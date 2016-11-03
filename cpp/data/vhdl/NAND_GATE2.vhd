--- BEGIN_PIN_INFO ---
-- X in --
-- Y in --
-- F2 out --
--- END_PIN_INFO ---

--- BEGIN_CODE ---

LIBRARY IEEE; 
USE IEEE.STD_LOGIC_1164.ALL; 
USE IEEE.STD_LOGIC_ARITH.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;


entity NAND_GATE2 is
--- BEGIN_PORT_DEF ---
port(
	X:	in std_logic;
	Y:	in std_logic;
	F2:	out std_logic
);
--- END_PORT_DEF ---
end NAND_GATE2;

architecture NAND_GATE2_behv of NAND_GATE2 is
begin
	F2 <= X nand Y;
	
end NAND_GATE2_behv;

--- END_CODE ---