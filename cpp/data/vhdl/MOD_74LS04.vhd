LIBRARY IEEE; 
USE IEEE.STD_LOGIC_1164.ALL; 
USE IEEE.STD_LOGIC_ARITH.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL; 

--- BEGIN_PIN_INFO ---

--- X1 in ---
--- Y2 out ---
--- X3 in ---
--- Y4 out ---
--- X5 in ---
--- Y6 out ---
--- GND7 gnd ---
--- Y8 out ---
--- X9 in ---
--- Y10 out ---
--- X11 in ---
--- Y12 out ---
--- X13 in ---
--- VCC14 vcc ---

--- END_PIN_INFO ---

--- BEGIN_CODE ---
entity MOD_74LS04 is
--- BEGIN_PORT_DEF ---
port(
    X1, X3, X5, X9, X11, X13: in std_logic;
    Y2, Y4, Y6, Y8, Y10, Y12: out std_logic
);
--- END_PORT_DEF ---
end MOD_74LS04;


architecture MOD_74LS04_behv of MOD_74LS04 is

component NOT1 
port(
    X: in std_logic;
    F1: out std_logic
);
end component;

begin

    u1: NOT1 port map(X => X1, F1 => Y2);
    u2: NOT1 port map(X => X3, F1 => Y4);
    u3: NOT1 port map(X => X5, F1 => Y6);
    u4: NOT1 port map(X => X9, F1 => Y8);
    u5: NOT1 port map(X => X11, F1 => Y10);
    u6: NOT1 port map(X => X13, F1 => Y12);

end MOD_74LS04_behv;

--- END_CODE ---
