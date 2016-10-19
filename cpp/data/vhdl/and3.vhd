LIBRARY IEEE ; 
USE IEEE.STD_LOGIC_1164.ALL ; 
USE IEEE.STD_LOGIC_ARITH.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL ; 

entity and3 is
	port(
				a, b, c: in std_logic;
				y: out std_logic
		);

end and3;

architecture a3 of and3
	y <= (a and b and c)
end a3;