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
        line = filter_string(line, 'qwertyuiopasdfghjkl;zxcvbnm,1234567890');
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

if __name__ == '__main__':
    print filter_string('llj_bash hahahaha 123 456', '0123456789 ')
    print filter_string('llj_bash hahahaha 123 456', 'abcdefghijklmnopqrstuvwxyz')
    s = "input_1; 1; 1, 2, 3, 4, 5; 0\ninput_2; 0; 2, 4; 1"
    print parse_activate(s)
