MainMenu = {
    ----------------------------------------------------
    -- Table to define the list of assets
    ----------------------------------------------------
    assets = {
        [0] = { type="font", id = "charriot-font", file = "./assets/fonts/charriot.ttf", fontSize = 14 },
    },

    ----------------------------------------------------
    -- Table to define the list of entities
    ----------------------------------------------------
    entities = {
        [0] = {
            name = "header",
            layer = 6,
            components = {
                text = {
                    position = {
                        x = 200,
                        y = 0
                    },
                    fontFamily = "charriot-font",
                    value = "Choppermania"
                }
            }
        }
    }
}