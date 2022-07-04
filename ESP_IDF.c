idf.py set-target esp32
idf.py build
idf.py -p COM11 flash
idf.py -p COM11 monitor