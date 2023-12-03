import string

from flask import Flask, render_template, request, redirect
from urllib.parse import quote
import socket
import random

app = Flask(__name__)
server_address = ('127.0.0.1', 6379)

def reduction(text):
    while True:
        try:
            short_link = "".join(random.choice(string.ascii_uppercase + string.ascii_lowercase + string.digits) for x in range(random.randrange(8,9)))
            return short_link
        except:
            pass

@app.route('/', methods = ['GET', 'POST'])
def index():
    generated_link = None
    if request.method == 'POST':
        original_link = request.form['user_input']
        short_link = reduction(original_link)

        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            try:
                s.connect(server_address)
                s.sendall(f"PUSH!{short_link}!{original_link}\0".encode())
                print("Message sent successfully.")
                data = s.recv(1024)
                print(f"Response from server: {data.decode()}")
            except ConnectionRefusedError:
                print("Connection to the server failed")
        generated_link = f"http://127.0.0.1:5000/{short_link}"

    return render_template("index.html", output_link = generated_link)

@app.route('/<short_link>')
def redirect_to_original(short_link):
    if short_link == 'favicon.ico':
        return "Not Found"

    # Получаем оригинальную ссылку из базы данных
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        try:
            s.connect(server_address)
            s.sendall(f"HGET!{short_link}\0".encode())
            data = s.recv(1024)
            original_link = data.decode()
            # print("catch: " + original_link + "|end")
            s.sendall(f"end".encode())
        except ConnectionRefusedError:
            print("Connection to the server failed.")
            return "Internal Server Error"

    # Открытие оригинальной ссылки
    if original_link != "NOT_FOUND":
        return redirect(original_link)
    else:
        return render_template('!index.html')

if __name__ == "__main__":
    app.run(host='127.0.0.1', port=5000, debug=True)