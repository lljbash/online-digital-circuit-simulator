LIBRARY IEEE ; 
USE IEEE.STD_LOGIC_1164.ALL ; 
USE IEEE.STD_LOGIC_ARITH.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL ; 

entity notand4 is
	port(
				a, b, c, d: in std_logic;
				y:out std_logic
		);

end notand4;

architecture na4 of notand4 is
begin
	y <= NOT(a and b and c and d);
end na4;