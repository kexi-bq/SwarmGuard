# пример с pySX127x или своей обёрткой; тут оставим интерфейс-стаб
class Lora:
    def __init__(self, freq=433.0, bw=125e3, sf=7, cr=5):
        pass
    def begin(self):
        pass
    def recv(self) -> bytes:
        # вернуть bytes пакета или b'' если нет
        return b""
