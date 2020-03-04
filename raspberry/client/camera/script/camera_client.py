import io
import socket
import struct
import time
import picamera
import sys

def printUsage():
  print("Usage: python camera_client.py <server_ip> <port_no>")

def main():
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

  connection = client_socket.makefile('wb')
  try:
    with picamera.PiCamera() as camera:
      camera.resolution = (320, 240)
      print("Starting camera...........")
      time.sleep(2)
      print("Lets go")
      stream = io.BytesIO()        
      for foo in camera.capture_continuous(stream, 'jpeg'):
        connection.write(struct.pack('<L', stream.tell()))
        connection.flush()
        stream.seek(0)
        connection.write(stream.read())
        stream.seek(0)
        stream.truncate()
  except:
    print("Close connection")
    connection.close()
    client_socket.close()

if __name__ == "__main__":
  main()