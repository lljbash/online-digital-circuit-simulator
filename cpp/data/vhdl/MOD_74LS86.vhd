--- BEGIN_PIN_INFO ---

--- X1 in ---
--- X2 in ---
--- Y3 out ---
--- X4 in ---
--- X5 in ---
--- Y6 out ---
--- GND7 gnd ---
--- Y8 out ---
--- X9 in ---
--- X10 in ---
--- Y11 out ---
--- X12 in ---
--- X13 in ---
--- VCC14 vcc ---

--- END_PIN_INFO ---

--- BEGIN_CODE ---

LIBRARY IEEE ; 
USE IEEE.STD_LOGIC_1164.ALL ; 
USE IEEE.STD_LOGIC_ARITH.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL ; 


entity MOD_74LS86 is
--- BEGIN_PORT_DEF ---
port(
    X1, X2, X4, X5, X9, X10, X12, X13: in std_logic;
	Y3, Y6, Y8, Y11: out std_logic
);
--- END_PORT_DEF ---
end MOD_74LS86;

architecture MOD_74LS86_behv of MOD_74LS86 is

component XOR_GATE2 
port(
	a, b: in std_logic;
	f: out std_logic
);
end component;

begin

	u1: XOR_GATE2 port map(a => X1, b => X2, f => Y3);
	u2: XOR_GATE2 port map(a => X4, b => X5, f => Y6);
	u3: XOR_GATE2 port map(a => X9, b => X10, f => Y8);
	u4: XOR_GATE2 port map(a => X12, b => X13, f => Y11);

end MOD_74LS86_behv;

--- END_CODE ---