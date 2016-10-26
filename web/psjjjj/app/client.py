import sys
import socket

class MyClient:
    __host = '127.0.0.1'
    __port = 1234

    def connect(self):
        try:
            self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        except socket.error:
            print 'Failed to create socket'
            sys.exit()
        try:
            remote_ip = socket.gethostbyname(self.__host)
        except socket.gaierror:
            print 'Hostname could not be resolved. Exiting'
            sys.exit()
        self.s.connect((remote_ip, self.__port))
        print 'Socket connected to ' + self.__host + ' on ip ' + remote_ip
    def sendMessage(self, message):
        try:
            message_str = message.SerializeToString()
            self.s.sendall(message_str)
        except socket.error:
            print 'Send failed'
            sys.exit()
        print 'Message send successfully!'
    def recvMessage(self):
        reply = self.s.recv(1048576)
        return reply
    def close(self, number):
        self.s.shutdown(number)
        self.s.close()
