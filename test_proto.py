import sys
import time
import User.demo_pb2 as demo_pb2
import serial
import serial.tools.list_ports

if __name__ == "__main__":
    # print(serial.tools.list_ports.comports())
    for port in serial.tools.list_ports.comports():
        print(port)

    conn = serial.Serial(port="COM5", baudrate='115200')
    print(conn)

    while True:
        try:
            # print(conn.inWaiting())
            if conn.inWaiting() > 0:
                pb = demo_pb2.Person()
                conn_read = conn.read(conn.inWaiting())
                print(conn_read)
                pb.ParseFromString(conn_read)
                print(pb)

        except Exception as e:
            info=sys.exc_info()  
            print (info[0],":",info[1])

        
        time.sleep(0.1)
