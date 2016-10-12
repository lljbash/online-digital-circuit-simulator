LIBRARY IEEE ; 
USE IEEE.STD_LOGIC_1164.ALL ; 
USE IEEE.STD_LOGIC_ARITH.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL ; 

entity my74LS00 is
	port(
		inpu: in std_logic_vector(7 downto 0);
		outpu: out std_logic_vector(3 downto 0)
		);
end my74LS00;

architecture LS00 of my74LS00 is

	component notand2 
		port(
				a, b: in std_logic;
				y: out std_logic
			);
	end component;

	begin

	u1: notand2 port map(a => inpu(0), b => inpu(1), y => outpu(0));
	u2: notand2 port map(a => inpu(2), b => inpu(3), y => outpu(1));
	u3: notand2 port map(a => inpu(4), b => inpu(5), y => outpu(2));
	u4: notand2 port map(a => inpu(6), b => inpu(7), y => outpu(3));

	end LS00;