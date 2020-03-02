import signal
from xbox360controller import Xbox360Controller
import time, threading
import socket
import sys
import pickle

HEADSIZE = 10

def printUsage():
  print("Usage: python xbox_controller_server.py <server_ip> <port_no>")

def main():
  server_socket = socket.socket()
  if len(sys.argv) != 3:
    printUsage()
    exit(-1)
  server_socket.bind((sys.argv[1], int(sys.argv[2])))  
  while True:
    try:
      server_socket.listen(0)
      print("Waiting for client")
      client_socket, client_address = server_socket.accept()
      print("Start writing to {0}".format(client_address))
      with Xbox360Controller(0) as controller:
        while True:
          getXboxData(controller, client_socket)
          time.sleep(0.1)
    except IOError:
      pass

def getXboxData(controller, client_socket):
  axis_l_name = controller.axis_l.name
  axis_l_x    = math.floor(controller.axis_l.x * 256)
  axis_l_y    = math.floor(controller.axis_l.y * 256)
  axis_r_name = controller.axis_r.name
  axis_r_x    = math.floor(controller.axis_r.x * 256)
  axis_r_y    = math.floor(controller.axis_r.y * 256)

  button_a_name    = controller.button_a.name
  button_a_pressed = controller.button_a.is_pressed
  button_b_name    = controller.button_b.name
  button_b_pressed = controller.button_b.is_pressed
  button_x_name    = controller.button_x.name
  button_x_pressed = controller.button_x.is_pressed
  button_y_name    = controller.button_y.name
  button_y_pressed = controller.button_y.is_pressed
    
  data = { 
    "lx" : axis_l_x,
    "ly" : axis_l_y,
    "rx" : axis_r_x,
    "ry" : axis_r_y,
    "a"  : button_a_pressed,
    "b"  : button_b_pressed,
    "x"  : button_x_pressed,
    "y"  : button_y_pressed,
  }

  print(data)

  global HEADSIZE
  msg = pickle.dumps(data)
  msg = bytes(f'{len(msg):<{HEADSIZE}}', "utf-8") + msg
  client_socket.send(msg)

if __name__ == "__main__":
  main()

