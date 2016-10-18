LIBRARY IEEE ; 
USE IEEE.STD_LOGIC_1164.ALL ; 
USE IEEE.STD_LOGIC_ARITH.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL ; 

entity my74LS86 is
	port(
		inpu: in std_logic_vector(7 downto 0);
		outpu: out std_logic_vector(3 downto 0)
		);
end my74LS86;

architecture LS86 of my74LS86 is

	component xor2 
		port(
				a, b: in std_logic;
				y: out std_logic
			);
	end component;

	begin

	u1: xor2 port map(a => inpu(0), b => inpu(1), y => outpu(0));
	u2: xor2 port map(a => inpu(2), b => inpu(3), y => outpu(1));
	u3: xor2 port map(a => inpu(4), b => inpu(5), y => outpu(2));
	u4: xor2 port map(a => inpu(6), b => inpu(7), y => outpu(3));

	end LS86;