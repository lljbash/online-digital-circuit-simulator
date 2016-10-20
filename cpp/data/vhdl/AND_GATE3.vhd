LIBRARY IEEE ; 
USE IEEE.STD_LOGIC_1164.ALL ; 
USE IEEE.STD_LOGIC_ARITH.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL ; 

--- BEGIN_PIN_INFO ---
--- a in ---
--- b in ---
--- c in ---
--- f out ---
--- END_PIN_INFO ---

--- BEGIN_CODE ---
entity AND_GATE3 is
--- BEGIN_PORT_DEF ---
port(
	a, b, c: in std_logic;
	f: out std_logic
);
--- END_PORT_DEF ---
end AND_GATE3;

architecture AND_GATE3_behv of AND_GATE3 is
	f <= (a and b and c)
end AND_GATE3_behv;

--- END_CODE ---