LIBRARY IEEE ; 
USE IEEE.STD_LOGIC_1164.ALL ; 
USE IEEE.STD_LOGIC_ARITH.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL ; 

entity xor2 is
	port(
				a, b: in std_logic;
				y:out std_logic
		);

end xor2;

architecture x2 of xor2 is
begin
	y <= a xor b;
end x2;