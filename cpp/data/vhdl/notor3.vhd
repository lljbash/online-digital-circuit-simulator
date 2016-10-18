LIBRARY IEEE ; 
USE IEEE.STD_LOGIC_1164.ALL ; 
USE IEEE.STD_LOGIC_ARITH.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL ; 

entity notor3 is
	port(
				a, b, c: in std_logic;
				y:out std_logic
		);

end notor3;

architecture no3 of notor3 is
begin
	y <= NOT(a or b or c);
end no3;