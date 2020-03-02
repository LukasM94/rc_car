import io
import socket
import struct
from PIL import Image
import cv2
import numpy
import sys

def printUsage():
  print("python camera_server.py 0.0.0.0 <port_no>")

def main():
  if len(sys.argv) != 3:
    printUsage()
    exit(-1)
  server_socket = socket.socket()
  server_socket.bind((sys.argv[1], int(sys.argv[2])))  
  server_socket.listen(0)
  print("Waiting for a client")
  connection = server_socket.accept()[0].makefile('rb')
  print("Start receiving camera pictures")
  try:
    img = None
    while True:
      image_len = struct.unpack('<L', connection.read(struct.calcsize('<L')))[0]
      if not image_len:
        break
      image_stream = io.BytesIO()
      image_stream.write(connection.read(image_len))
      image_stream.seek(0)
      image = Image.open(image_stream)
      im = cv2.cvtColor(numpy.array(image), cv2.COLOR_RGB2BGR)
      cv2.imshow('Video',im)
      if cv2.waitKey(1) & 0xFF == ord('q'):
        break
    cv2.destroyAllWindows()
  except:
    connection.close()
    server_socket.close()
    print("Close connection")

if __name__ == "__main__":
  main()