#include "FileLogger.h"

#include <atomic>
#include <condition_variable>
#include <filesystem>
#include <fstream>
#include <queue>
#include <thread>
#include <vector>

const int THREADS_COUNT = 2;



class FileLogger::Impl
{
public:
	Impl();
	~Impl();

	std::mutex _mutex;
	std::condition_variable _condition;

	struct Note
	{
		time_t _time;
		std::string _str;
	};
	std::queue<Note> _notes;

private:
	std::vector<std::thread> _threads;
	std::atomic<bool> _stopped { false };

	void workerThread(int threadId);
	void processNote(const Note &note, int threadId) const;
	std::string makeFileName(time_t time, int threadId) const;
};



FileLogger::Impl::Impl()
{
	for (int i = 0; i < THREADS_COUNT; ++i)
	{
		int threadId = i + 1;
		_threads.emplace_back(&Impl::workerThread, this, threadId);
	}
}



FileLogger::Impl::~Impl()
{
	{
		std::unique_lock lock { _mutex };
		_stopped = true;
	}

	_condition.notify_all();

	for (auto &thread : _threads)
	{
		thread.join();
	}
}



void FileLogger::Impl::workerThread(int threadId)
{
	std::unique_lock lock { _mutex };

	while (!_stopped)
	{
		while (!_stopped && _notes.empty())
		{
			_condition.wait(lock);
		}

		while (!_notes.empty())
		{
			auto note = _notes.front();
			_notes.pop();

			lock.unlock();
			processNote(note, threadId);
			_condition.notify_all();

			lock.lock();
		}
	}
}



void FileLogger::Impl::processNote(const Note &note, int threadId) const
{
	auto fileName = makeFileName(note._time, threadId);
	std::ofstream out;
//	out.open(fileName);
//	if (out.is_open())
//	{
//		out << note._str << std::endl;
//	}
//	out.close();
}



std::string FileLogger::Impl::makeFileName(time_t time, int threadId) const
{
	auto fileNameBase = "bulk" + std::to_string(time) + "_thread_" + std::to_string(threadId);
	auto fileName = fileNameBase + ".log";

	int i = 1;
	while (std::filesystem::exists(fileName))
	{
		fileName = fileNameBase + "_" + std::to_string(++i) + ".log";
	}

	return fileName;
}



FileLogger::FileLogger()
	: _impl { new Impl }
{
}



FileLogger::~FileLogger()
{
	delete _impl;
}



void FileLogger::log(time_t time, const std::string &str)
{
	{
		std::unique_lock lock { _impl->_mutex };
		_impl->_notes.push({ time, str });
	}

	_impl->_condition.notify_one();
}



void FileLogger::finishWork() const
{
	std::unique_lock lock { _impl->_mutex };
	while (!_impl->_notes.empty())
	{
		_impl->_condition.wait(lock);
	}
}
