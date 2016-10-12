from ModuleProto_pb2 import AllModulesProto, SimpleModuleProto

def addPin(pin, i):
    pin.index = i
    print("Now set pin" + str(i) + "-------")
    pin.pos_X = float(raw_input("pos_X:"))
    pin.pos_Y = float(raw_input("pos_Y:"))

def addGate(gate, i):
    print("Now set gate" + str(i) + "------")
    gate.type = raw_input("type:")
    in_str = raw_input("index of in pins(splited by space):")
    ins = in_str.split(" ")
    for i in ins:
        gate.pins_in.append(int(i))
    gate.pin_out = int(raw_input("index of out pin:"))

def addModule():
    module = allModules.modules.add()
    module.name = raw_input("name:")
    pin_num = int(raw_input("pin_num:"))
    for i in range(0, pin_num):
        addPin(module.pins.add(), i) 
    gate_num = int(raw_input("gate_num:"))
    for i in range(0, gate_num):
        addGate(module.gates.add(), i)
    print "Add a module successfully!"
    show(module.name)
    try:
        f = open("allModules",'wb')
        f.write(allModules.SerializeToString())
    finally:
        f.close()

def show(name):
    for module in allModules.modules:
        if module.name == name:
            print("----------------------name-----------------------")
            print(name)
            print("----------------------pins-----------------------")
            for pin in module.pins:
                print("pin" + str(pin.index) + ": (" + str(pin.pos_X) + " , " + str(pin.pos_Y) + ")")
            print("----------------------gates----------------------")
            for gate in module.gates:
                print("------------------")
                print("type : " + gate.type)
                print("pins in : "),
                for i in gate.pins_in:  
                    print(i),
                print
                print("pin out : " + str(gate.pin_out))
            print("-------------------------------------------------")
            return
    print("Can't find a module named " + name + "!")

def delete(name):
    i = 0;
    for module in allModules.modules:
        if module.name == name:
             del allModules.modules[i]
             return
        i = i + 1
    print("Can't find a module named " + name + "!")   

def showAll():
    for module in allModules.modules:
        print(module.name),
    print
                 
try:
    f = open("allModules",'rb')
    modules = f.read()
finally:
    f.close()
    
allModules = AllModulesProto()

if (len(modules) != 0):
    allModules.ParseFromString(modules)

while (True):
    i = raw_input("Give me some instructions!\nadd      add a module\nshow     show information of the module\nall      show all module names\ndelete   delete a module\nquit     quit\ninstruction:")
    if i == "add":
        addModule()
    elif i == "show":
        name = raw_input("module name:")
        show(name)
    elif i == "quit":
        break
    elif i == "delete":
        name = raw_input("module name:")
        delete(name)
    elif i == "all":
        showAll()
    else:
        print("unknown instruction!")
    

f = open("allModules", 'wb')
f.write(allModules.SerializeToString()) 
f.close() 
