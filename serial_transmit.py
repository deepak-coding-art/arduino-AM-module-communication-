import serial
import time
import os

ser = serial.Serial('COM5', baudrate=250000, timeout=1)
time.sleep(3)

numpoints = 10
data_list = [0]*numpoints
arr_index = 0
file_name = "Test_2.bmp"  # put file name in cots with extension


def file_set():
    file_length_in_bytes = os.path.getsize(file_name)
    print(file_length_in_bytes)
    return file_length_in_bytes


size_of_data = file_set()
arr = [0for i in range(size_of_data)]
loops = size_of_data/numpoints


def set_binary_arr():
    with open(file_name, "rb") as binary_file:
        print("8 Bit Numbers:-")

        for num in range(size_of_data):
            binary_file.seek(num)
            couple_bytes = binary_file.read(1)
            i = int.from_bytes(couple_bytes, byteorder='big')
            arr[num] = i


def get():
    ser.write(b'g')
    for i in range(numpoints):
        str_input = ser.readline().decode().split('\r\n')
        data = int(str_input[0])
        data_list[i] = data
    print(data_list)


def write(arr_ind):
    if arr_ind >= size_of_data:
        arr_ind = 0
        return arr_ind
    else:
        ser.write(b'w')
        for i in range(numpoints):
            ser.write(str(arr[arr_ind]).encode())
            ser.write('\n'.encode())
            arr_ind += 1
        return arr_ind


def erase():
    ser.write(b'e')


def transmit():
    timer = b''
    ser.write(b't')
    while timer != b'd':
        timer = ser.read()


set_binary_arr()


while 1:
    userInput = input('Press r for read, e for erase, w for write, q for quit, t for transfer,'
                      ' s for auto sent k for reset')
    if userInput == 's':
        for p in range(int(loops)):
            if userInput == 'r':
                get()
            if userInput == 'w' or userInput == 's':
                arr_index = write(arr_index)
                if arr_index == 0:
                    break
                time.sleep(0.02)
            if userInput == 't' or userInput == 's':
                transmit()
            if userInput == 'e' or userInput == 's':
                erase()
                time.sleep(0.01)
            if userInput == 'q':
                arr_index = 0
                break
        userInput = 't'
    if userInput == 'r':
        get()
    if userInput == 'w':
        arr_index = write(arr_index)
        if arr_index == 0:
            break
        time.sleep(0.05)
    if userInput == 't':
        transmit()
        time.sleep(0.05)
    if userInput == 'e':
        erase()
        time.sleep(0.05)
    if userInput == 'k':
        arr_index = 0
    if userInput == 'q':
        arr_index = 0
        break
