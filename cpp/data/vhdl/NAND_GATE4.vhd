LIBRARY IEEE ; 
USE IEEE.STD_LOGIC_1164.ALL ; 
USE IEEE.STD_LOGIC_ARITH.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL ; 

--- BEGIN_PIN_INFO ---
--- a in ---
--- b in ---
--- c in ---
--- d in ---
--- f out ---
--- END_PIN_INFO ---

--- BEGIN_CODE ---
entity NAND_GATE4 is
--- BEGIN_PORT_DEF ---
port(
	a, b, c, d: in std_logic;
	f: out std_logic
);
--- END_PORT_DEF ---
end NAND_GATE4;

architecture NAND_GATE4_behv of NAND_GATE4 is
begin
	f <= NOT(a and b and c and d);
end NAND_GATE4_behv;

--- END_CODE ---