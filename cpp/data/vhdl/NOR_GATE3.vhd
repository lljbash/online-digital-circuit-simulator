--- BEGIN_PIN_INFO ---
--- a in ---
--- b in ---
--- c in ---
--- f out ---
--- END_PIN_INFO ---

--- BEGIN_CODE ---

LIBRARY IEEE ; 
USE IEEE.STD_LOGIC_1164.ALL ; 
USE IEEE.STD_LOGIC_ARITH.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL ; 

entity NOR_GATE3 is
--- BEGIN_PORT_DEF ---
port(
	a, b, c: in std_logic;
	f: out std_logic
);
--- END_PORT_DEF ---
end NOR_GATE3;

architecture NOR_GATE3_behv of NOR_GATE3 is
begin
	f <= not(a or b or c);
end NOR_GATE3_behv;

--- END_CODE ---