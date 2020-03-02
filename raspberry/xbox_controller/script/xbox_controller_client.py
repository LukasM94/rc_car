import socket
import time
import sys
import pickle

HEADERSIZE = 10

def printUsage():
  print("Usage: python xbox_controller_client.py <server_ip> <port_no>")

def getSocket():
  server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
  server_socket.connect((sys.argv[1], int(sys.argv[2])))
  return server_socket

def main():
  global HEADERSIZE
  if len(sys.argv) != 3:
    printUsage()
    exit(-1)
  
  tries = 0
  while True:
    try:
      server_socket = getSocket()
      break
    except socket.error:
      if tries == 5:
        print("Stop waiting of the server")
        exit(-2)
      tries += 1
      print("Wait {0} second and try again to connect to the server".format(sec))
      time.sleep(sec)
  print("Connected to server {0}:{1}".format(sys.argv[1], sys.argv[2]))

  while True:
    full_msg = b''
    new_msg  = True
    length_msg = 0
    while True:
      # print("len(full_msg) - HEADERSIZE == length_msg: {0} == {1}".format(len(full_msg) - HEADERSIZE, length_msg))
      msg = server_socket.recv(16)
      if new_msg == True:
        print("New message length is {0}".format(msg[:HEADERSIZE]))
        try:
          length_msg = int(msg[:HEADERSIZE])
        except:
          print("ups")
          server_socket = getSocket()
          break
        new_msg    = False

      full_msg += msg

      if len(full_msg) - HEADERSIZE >= length_msg:
        data      = pickle.loads(full_msg[HEADERSIZE:])
        milli_sec = int(round(time.time() * 1000))
        print("{0}: {1}".format(milli_sec, data))

        new_msg = True
        full_msg = b''

if __name__ == "__main__":
  main()