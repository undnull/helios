core.include "assets/scripts/test_1.lua"
core.include "assets/scripts/test_2.lua"

event.hook("game.main", function()
    logger.log("game.main event called")
end)
