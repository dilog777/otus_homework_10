#!/usr/bin/env python3

import socket
import sys
import re

def read_args() -> tuple[str, bytes]:
    if len(sys.argv) < 2:
        print(f'Usage: sys.argv[0] <host:port>')
        sys.exit(1)

    host_port = sys.argv[1]
    if ':' not in host_port:
        print("Error: Invalid host:port format.")
        sys.exit(1)

    host, port = host_port.split(':')
    try:
        port = int(port)
    except ValueError:
        print("Error: Port must be an integer.")
        sys.exit(1)

    return host, port

def main():
    host, port = read_args()

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as connection:
        connection.connect((host, port))

        while True:
            user_input = input('Enter log message: ')
            print('Sending...')
            connection.sendall(f'{user_input}\n'.encode())

if __name__ == '__main__':
    main()
