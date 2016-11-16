import py2proto.circuit_pb2 as pb

def filter_string(s, char_set):
    s2 = s.lower()
    for c in s2:
        if not c in char_set:
            s = s.replace(c, '')
    return s

def parse_activate(text):
    lines = text.split('\n')
    acts = []
    for line in lines:
        act = pb.CircuitProto.Chip.Activation()
        line = filter_string(line, 'qwertyuiopasdfghjkl;zxcvbnm,1234567890')
        l = [item for item in line.split(';') if item != '']
        if len(l) < 4:
            continue
        [name, initial_str, jumping_time_str, repeat_str] = l[:4]
        if initial_str == '0':
            act.initial = False
        elif initial_str == '1':
            act.initial = True
        else:
            continue
        jumping_times = jumping_time_str.split(',')
        for jumping_time in jumping_times:
            time = filter_string(jumping_time, '1234567890')
            if time == '':
                continue
            act.jumping_time.append(int(time))
        if repeat_str == '0':
            act.repeat = False
        elif repeat_str == '1':
            act.repeat = True
        else:
            continue
        acts.append([name, act])
    return acts

def activate_to_svg(acts):
    kLeft = 100
    kPs = 5
    kTime = 100
    kUpDown = 10
    kA = 50
    kH = kUpDown + kA + kUpDown
    w = kLeft + kPs * kTime
    h = kH * len(acts)
    svg = '<svg height="%d" width="%d">\n'%(h + 20, w)
    cnt = 0
    for [name, act] in acts:
        cnt = cnt + 1
        x0 = kLeft
        x = x0
        yH = kH * cnt - kUpDown - kA
        yL = yH + kA
        current_logic = act.initial
        y = yH if act.initial else yL
        svg += '  <text x="%d" y="%d" fill="black">%s</text>'%(0, yL - 10, name)
        svg += '  <polyline points="%d,%d'%(x, y)
        while True:
            for time in act.jumping_time:
                x = x0 + time * kPs
                svg += ' %d,%d'%(x, y)
                current_logic = not current_logic
                y = yH if current_logic else yL
                svg += ' %d,%d'%(x, y)
            x0 = x
            if (not act.repeat) or x0 >= w:
                break
        svg += ' %d %d'%(w, y)
        svg += '" style="fill:none;stroke:black;stroke-width:2" />\n'
    for x in range(0, kTime, 5):
        svg += '  <text x="%d" y="%d" fill="black">%d</text>\n'%(kLeft + kPs * x - 5, h + 20, x)
    svg += '  <polyline points="'
    for x in range(0, kTime, 5):
        svg += '%d,%d '%(kLeft + kPs * x, h + 3)
        svg += '%d,%d '%(kLeft + kPs * x, h)
        svg += '%d,%d '%(kLeft + kPs * x, h + 3)
    svg += '%d,%d" style="fill:none;stroke:black;stroke-width:2" />\n'%(w, h + 3)
    svg += 'Sorry, your browser does not support inline SVG.\n'
    svg += '</svg>\n'
    return svg

if __name__ == '__main__':
    print filter_string('llj_bash hahahaha 123 456', '0123456789 ')
    print filter_string('llj_bash hahahaha 123 456', 'abcdefghijklmnopqrstuvwxyz')
    s = "input_1; 1; 1, 2, 3, 4, 5; 0\ninput_2; 0; 2, 4; 1"
    acts = parse_activate(s)
    print acts
    print activate_to_svg(acts)
