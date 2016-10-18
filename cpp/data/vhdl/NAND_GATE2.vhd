LIBRARY IEEE; 
USE IEEE.STD_LOGIC_1164.ALL; 
USE IEEE.STD_LOGIC_ARITH.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;

--- BEGIN_PIN_INFO ---
-- X in --
-- Y in --
-- F2 out --
--- END_PIN_INFO ---

--- BEGIN_CODE ---

entity NAND_GATE2 is
--- BEGIN_PORT_DEF ---
port(
	X:	in std_logic;
	Y:	in std_logic;
	F2:	out std_logic
);
--- END_PORT_DEF ---
end NAND_GATE2;

architecture behv of NAND_GATE2 is
begin
process(X,Y)
begin
	F2 <= X nand Y;
end process;
end behv;

--- END_CODE ---