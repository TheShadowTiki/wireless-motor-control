# -*- coding: utf-8 -*-
"""
Created on Wed Jul 17 03:30:11 2024

@author: mikoz
"""

from flask import Flask, request, jsonify, render_template
import requests

app = Flask(__name__)

# Replace with the IP address of your ESP32
# ESP32_IP = 'http://<ESP32_IP_ADDRESS>'

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/set_speed', methods=['POST'])
def set_speed():
    speed = request.form.get('speed')
    if speed:
        speed = int(speed)
        if 0 <= speed <= 100:
            try:
                response = requests.get(f'{ESP32_IP}/speed/{speed}')
                if (response.status_code == 200):
                    return jsonify(message=f'Speed set successfully: {speed}%')
                else:
                    return jsonify(message='Failed to set speed', status=response.status_code)
            except requests.RequestException as e:
                return jsonify(message=f'Error: {e}')
        else:
            return jsonify(message='Error: Speed must be between 0 and 100.')
    return jsonify(message='Invalid speed')

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
