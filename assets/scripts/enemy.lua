--cant use yet, playerpos is in floats, can only use doubles.
--function updatePlayerPos(x, y, z)
--	playerPosX = x
--	playerPosY = y
--	playerPosZ = z
--end
function update(enemyPos, playerPos)
	
	if enemyPos > playerPos then
		value = -1.0
	elseif enemyPos < playerPos then
		value = 1.0
	end
	return value
end

