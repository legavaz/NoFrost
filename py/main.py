import time

temp_max = 30
temp_min = 25
temp = -90
ten_on = 0
k_on = 0
v_on = 0
ten_timer = 0;


def Kompressor(m_value):
    global ten_on
    global k_on
    global v_on

    # сигнал на отключение компрессора
    # до этого компрессор был выключен
    # и тен не работал
    if k_on == 1 and m_value == 0 and ten_on == 0:
        k_on = m_value
        Vent(0)
        Ten_warm(1)
    elif k_on == 0 and m_value == 1 and ten_on == 0:
        k_on = 1
        Vent(1)
    else:
        Ten_warm(0)


def Ten_warm(m_value):
    global ten_on
    global k_on
    global v_on
    global ten_timer

    if m_value == 1:
        ten_timer = time.time()
        ten_on = m_value
        Vent(0)
    elif m_value == 0:
        if ten_timer != 0 and ten_on == 1:
            r_timer = time.time() - ten_timer
            print("прошло времени (сек):", round(r_timer, 2))
            if r_timer >= 30:
                ten_on = m_value
                Vent(1)


def Vent(m_value):
    global ten_on
    global k_on
    global v_on
    v_on = m_value


def debag():
    # print('t:{0}; (min:{1} - max:{2})'.format(temp, temp_min, temp_max))
    print('S : V{0}/K{1}/T{2}'.format(v_on, k_on, ten_on))


def setup():
    global ten_on
    global k_on
    global v_on
    ten_on = 0
    k_on = 0
    v_on = 0


setup()

while True:
    temp = int(input('input new t({0}-{1}) : '.format(temp_min, temp_max)))
    if temp >= temp_max:
        Kompressor(1)
    elif temp <= temp_min:
        Kompressor(0)

    debag()
    if temp < -100:
        break
