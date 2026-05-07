import serial
import time

ser = None

def connect_system(port='COM3', baud=115200):
    global ser
    try:
        if ser and ser.is_open:
            ser.close()
        ser = serial.Serial(port, baud, timeout=0.1)
        time.sleep(2)
        ser.reset_input_buffer()
        return True 
    except:
        return False

def inputHandshake():
    global ser
    if ser and ser.is_open:
        ser.write(b'HELLO_ESP\n')
        time.sleep(0.5)
        if ser.in_waiting > 0:
            response = ser.readline().decode('utf-8', errors='ignore').strip()
            return response
    return None

def get_latest_data():
    global ser
    if ser and ser.is_open and ser.in_waiting > 0:
        try:
            line = ser.readline().decode('utf-8', errors='ignore').strip()
            return line
        except:
            return None
    return None