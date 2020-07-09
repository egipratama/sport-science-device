from flask import Flask, request
import requests

app = Flask(__name__)

@app.route('/')
def index():
        return 'Hello world'
@app.route('/data')
def data():
        id = request.args.get('id')
        data = request.args.get('data')
        track = request.args.get('track')
        gate = request.args.get('gate')

        url = "https://us-central1-unikom-sport-science.cloudfunctions.net/runnin$
        res = requests.get(url)
        print(res.text)
        return 'berhasil' + id
if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0')
