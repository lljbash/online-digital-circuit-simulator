LIBRARY IEEE ; 
USE IEEE.STD_LOGIC_1164.ALL ; 
USE IEEE.STD_LOGIC_ARITH.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL ; 

entity my74LS20 is
	port(
		inpu: in std_logic_vector(7 downto 0);
		outpu: out std_logic_vector(1 downto 0)
		);
end my74LS20;

architecture LS20 of my74LS20 is

	component notand4 
		port(
				a, b, c, d: in std_logic;
				y: out std_logic
			);
	end component;

	begin

	u1: notand4 port map(a => inpu(0), b => inpu(1), c => inpu(2), d => inpu(3), y => outpu(0));
	u2: notand4 port map(a => inpu(4), b => inpu(5), c => inpu(6), d => inpu(7), y => outpu(1));

	end LS20;