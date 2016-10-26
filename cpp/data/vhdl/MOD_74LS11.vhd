--- BEGIN_PIN_INFO ---

--- X1 in ---
--- X2 in ---
--- X3 in ---
--- X4 in ---
--- X5 in ---
--- Y6 out ---
--- GND7 gnd ---
--- Y8 out ---
--- X9 in ---
--- X10 in ---
--- X11 in ---
--- Y12 out ---
--- X13 in ---
--- VCC14 vcc ---

--- END_PIN_INFO ---

--- BEGIN_CODE ---

LIBRARY IEEE; 
USE IEEE.STD_LOGIC_1164.ALL; 
USE IEEE.STD_LOGIC_ARITH.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL; 

entity MOD_74LS11 is
--- BEGIN_PORT_DEF ---
port(
        X1, X2, X3, X4, X5, X9, X10, X11, X13: in std_logic;
        Y6, Y8, Y12: out std_logic
);
--- END_PORT_DEF ---
end MOD_74LS11;

architecture MOD_74LS11_behv of MOD_74LS11 is

component AND_GATE3 
port(
    a, b, c: in std_logic;
    f: out std_logic
    );
end component;

begin

    u1: AND_GATE3 port map(a => X1, b => X2, c => X13, f => Y12);
    u2: AND_GATE3 port map(a => X3, b => X4, c => X5, f => Y6);
    u3: AND_GATE3 port map(a => X9, b => X10, c => X11, f => Y8);

end MOD_74LS11_behv;

--- END_CODE ---
