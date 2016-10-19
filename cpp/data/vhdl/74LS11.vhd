LIBRARY IEEE ; 
USE IEEE.STD_LOGIC_1164.ALL ; 
USE IEEE.STD_LOGIC_ARITH.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL ; 

entity my74LS11 is
	port(
		inpu: in std_logic_vector(8 downto 0);
		outpu: out std_logic_vector(2 downto 0)
		);
end my74LS11;

architecture LS11 of my74LS11 is

	component and3 
		port(
				a, b, c: in std_logic;
				y:out std_logic
			);
	end component;

	begin

	u1: and3 port map(a => inpu(0), b => inpu(1), c => inpu(2), y => outpu(0));
	u2: and3 port map(a => inpu(3), b => inpu(4), c => inpu(5), y => outpu(1));
	u3: and3 port map(a => inpu(6), b => inpu(7), c => inpu(8), y => outpu(2));

	end LS11;