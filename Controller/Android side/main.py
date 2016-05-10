from kivy.app import App
from kivy.uix.widget import Widget
from kivy.properties import ObjectProperty
from kivy.clock import Clock
import socket

hval = 0
vval = 0
aval = 90

TCP_IP = '192.168.4.1'
TCP_PORT = 80
BASE = "serwo="

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((TCP_IP, TCP_PORT))

class HeightSlider(Widget):
    pass

class VelocitySlider(Widget):
    pass

class AngleSlider(Widget):
    pass

class HoovercraftDriver(Widget):
    hslider = ObjectProperty(None)
    vslider = ObjectProperty(None)
    aslider = ObjectProperty(None)

    def update(self, dt):
        global hval, vval, aval
        lhval = hval + 35.0
        lvval = vval + 35.0
        s.sendall(BASE + chr(int(lhval)) + chr(int(lvval)) + chr(int(aval)) + "\n")


    def on_touch_move(self, touch):
        if touch.x < self.width / 5:
            if touch.y >= 5 and touch.y <= self.height - 10:
                global hval
                self.hslider.pos = 5, touch.y
                hval = (92.0 * touch.y)/(self.height - 10)

        if touch.x < 2 * self.width / 5 and touch.x > self.width / 5:
            if touch.y >= 5 and touch.y <= self.height - 10:
                global vval
                self.vslider.pos = self.width / 5 + 5, touch.y
                vval = (92.0 * touch.y)/(self.height - 10)

        if touch.x > 2 * self.width / 5:
            if touch.x < self.width - 10:
                global aval
                self.aslider.pos = touch.x, 5
                aval = (180.0 * (touch.x - 2.0/5.0 * self.width))/(3.0/5.0 * self.width - 5.0)


class HeightSlider(Widget):
    pass

class VelocitySlider(Widget):
    pass

class AngleSlider(Widget):
    pass

class HoovercraftApp(App):
    def build(self):
        app = HoovercraftDriver()
        Clock.schedule_interval(app.update, 1.0 / 10.0)
        return app

if __name__ == '__main__':
    HoovercraftApp().run()
