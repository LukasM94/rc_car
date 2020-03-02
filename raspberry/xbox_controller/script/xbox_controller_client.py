import socket
import time
import sys
import pickle

HEADERSIZE = 10

def printUsage():
  print("Usage: python xbox_controller_client.py <server_ip> <port_no>")

def main():
  global HEADERSIZE
  if len(sys.argv) != 3:
    printUsage()
    exit(-1)
  
  tries = 0
  while True:
    try:
      client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
      client_socket.connect((sys.argv[1], int(sys.argv[2])))
      break
    except socket.error:
      if tries == 5:
        print("Stop waiting of the server")
        exit(-2)
      tries += 1
      print("Wait 5 second and try again to connect to the server")
      time.sleep(5)
  print("Connected to server {0}:{1}".format(sys.argv[1], sys.argv[2]))

  while True:
    full_msg = b''
    new_msg  = True
    while True:
      msg = client_socket.recv(16)
      if new_msg == True:
        print("New message length is {0}".format(msg[:HEADERSIZE]))
        length_msg = int(msg[:HEADERSIZE])
        new_msg    = False

      full_msg += msg

      if len(full_msg) - HEADERSIZE == length_msg:
        print("full msg received")

        data = pickle.loads(full_msg[HEADERSIZE:])
        print(data)

        new_msg = True
        full_msg = b''


if __name__ == "__main__":
  main()