#include "FileLogger.h"

#include <atomic>
#include <condition_variable>
#include <iostream>
#include <fstream>
#include <queue>
#include <thread>
#include <vector>

const unsigned int THREADS_COUNT = 2;



class FileLogger::Impl
{
public:
	Impl();
	~Impl();

	void log(time_t time, const std::string &str);

private:
	struct Note
	{
		time_t _time;
		std::string _str;
	};

	std::condition_variable _condition;
	std::queue<Note> _notes;
	std::mutex _mutex;
	std::vector<std::thread> _threads;
	std::atomic<bool> _stopped { false };

	void workerThread();
	void processNote(const Note &note) const;
};



FileLogger::Impl::Impl()
{
	for (int i = 0; i < THREADS_COUNT; ++i)
	{
		_threads.emplace_back(&Impl::workerThread, this);
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



void FileLogger::Impl::log(time_t time, const std::string &str)
{
	{
		std::unique_lock lock { _mutex };
		_notes.push({ time, str });
	}

	_condition.notify_one();
}



void FileLogger::Impl::workerThread()
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
			processNote(note);
			lock.lock();
		}
	}
}



void FileLogger::Impl::processNote(const Note &note) const
{
	std::cout << std::this_thread::get_id() << " " << note._time << " " << note._str << std::endl;

//	auto fileName = "bulk" + std::to_string(timeStamp) + ".log";
//	std::ofstream out;
//	out.open(fileName);
//	if (out.is_open())
//	{
//		out << str << std::endl;
//	}
//	out.close();
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
	_impl->log(time, str);
}
