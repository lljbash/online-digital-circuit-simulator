LIBRARY IEEE ; 
USE IEEE.STD_LOGIC_1164.ALL ; 
USE IEEE.STD_LOGIC_ARITH.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL ; 

entity not1 is
	port(
				a: in std_logic;
				y: out std_logic
		);

end not1;

architecture not of not1 is
begin
	y <= NOT(a);
end not;