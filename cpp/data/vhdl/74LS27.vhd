LIBRARY IEEE ; 
USE IEEE.STD_LOGIC_1164.ALL ; 
USE IEEE.STD_LOGIC_ARITH.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL ; 

entity my74LS27 is
	port(
		inpu: in std_logic_vector(8 downto 0);
		outpu: out std_logic_vector(2 downto 0)
		);
end my74LS27;

architecture LS27 of my74LS27 is

	component notor3 
		port(
				a, b, c: in std_logic;
				y: out std_logic
			);
	end component;

	begin

	u1: notor3 port map(a => inpu(0), b => inpu(1), c => inpu(2), y => outpu(0));
	u1: notor3 port map(a => inpu(3), b => inpu(4), c => inpu(5), y => outpu(1));
	u1: notor3 port map(a => inpu(6), b => inpu(7), c => inpu(8), y => outpu(2));

	end LS27;