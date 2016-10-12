LIBRARY IEEE ; 
USE IEEE.STD_LOGIC_1164.ALL ; 
USE IEEE.STD_LOGIC_ARITH.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL ; 

entity my74LS04 is
	port(
		inpu: in std_logic_vector(5 downto 0);
		outpu: out std_logic_vector(5 downto 0)
		);
end my74LS04;

architecture LS04 of my74LS04 is

	component not1 
		port(
				a: in std_logic;
				y: out std_logic
			);
	end component;

	begin

	u1: not1 port map(a => inpu(0), y => outpu(0));
	u2: not1 port map(a => inpu(1), y => outpu(1));
	u3: not1 port map(a => inpu(2), y => outpu(2));
	u4: not1 port map(a => inpu(3), y => outpu(3));
	u5: not1 port map(a => inpu(1), y => outpu(1));
	end LS04;