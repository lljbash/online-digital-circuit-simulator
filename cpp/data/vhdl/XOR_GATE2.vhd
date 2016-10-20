LIBRARY IEEE ; 
USE IEEE.STD_LOGIC_1164.ALL ; 
USE IEEE.STD_LOGIC_ARITH.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL ; 

--- BEGIN_PIN_INFO ---
-- a in --
-- b in --
-- f out --
--- END_PIN_INFO ---

--- BEGIN_CODE ---
entity XOR_GATE2 is
--- BEGIN_PORT_DEF ---
port(
	a, b: in std_logic;
	f: out std_logic
);
--- END_PORT_DEF ---
end XOR_GATE2;

architecture XOR_GATE2_behv of XOR_GATE2 is
begin
	f <= a xor b;
end XOR_GATE2_behv;

--- END_CODE ---