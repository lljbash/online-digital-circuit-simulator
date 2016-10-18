LIBRARY IEEE; 
USE IEEE.STD_LOGIC_1164.ALL; 
USE IEEE.STD_LOGIC_ARITH.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;

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
entity MOD_74LS00 is
--- BEGIN_PORT_DEF ---
port(
	X1, X2, X4, X5, X9, X10, X12, X13: in std_logic;
	Y3, Y6, Y8, Y11: out std_logic
);
--- END_PORT_DEF ---
end MOD_74LS00;

architecture MOD_74LS00_behv of MOD_74LS00 is

component NAND_GATE2 
port(
	X: in std_logic;
	Y: in std_logic;
	F2: out std_logic
	);
end component;

begin

	u1: NAND_GATE2 port map(X => X1, Y => X2, F2 => Y3);
	u2: NAND_GATE2 port map(X => X4, Y => X5, F2 => Y6);
	u3: NAND_GATE2 port map(X => X9, Y => X10, F2 => Y8);
	u4: NAND_GATE2 port map(X => X12, Y => X13, F2 => Y11);

end MOD_74LS00_behv;

--- END_CODE ---