LIBRARY IEEE ; 
USE IEEE.STD_LOGIC_1164.ALL ; 
USE IEEE.STD_LOGIC_ARITH.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL ; 

entity notand2 is
	port(
				a, b: in std_logic;
				y:out std_logic
		);

end notand2;

architecture notand of notand2 is
begin
	y <= NOT(a and b);
end notand;