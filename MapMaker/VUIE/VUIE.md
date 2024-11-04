## V.U.I.E. - Void User Interface Engine

### Structs

    Definers 
            Functions and definitions

            Global Functions

            Vector2 Struct
                : x , y
    Atributes

        Position Type
        Position [ Include PositionType ]

        Size Type
        Size [ Include SizeType ]

        Color Type
        Color [ Include ColorType ]

        Info

    Modules
            Private Structs

        Transform [ Include Position , Size ] *

        ContainerBox [ Include Transform , Color[] ] **

    Elements
            Public Structs

        Base [ Include Info , Position , Size ] *
        
        Container [ Include Info, Transform , Color[] ] **

< ////////////////////////////////////////////////////////// >

### Types

    Position Types

        Cartesian: X , Y

        Polar: R , Theta

        Referencial: Global_X , Global_Y , Local_X , Local_Y

    Size Types

        Rectangle: Height , Width

        Circle: Radius, Points

        Polygon: Points[]

    Color Types

        <Temporary> ID

        RGB: Reg , Green , Blue

        HSV: Hue , Saturation , Value

        <Not Implemented> HEX: HexValue

    <Not Implemented> Text

    <Not Implemented> Image

< ////////////////////////////////////////////////////////// >

### Functions

    [Private] Create (Ct)
            : Creates the struct

    [Private] Delete (Dt)
            : Deletes the struct
    
    [Private] Set (St)
            : Sets the struct

    <Idea> [Private] get (Gt)
            : Returns the value of the struct
    
    <Not Implemented> Save
            : Saves on a file
    
    <Not Implemented> Load
            : Load on a file

    Render (R)
            : Calls other rendering related functions

    <Not Implemented> Process (P)
            : Basic Processing

    InternalArea (ItA)
            : Sets the internal area deleting the OUTSIDE area
    
    DrawInternal (DwI)
            : Draws everything Inside it

    <Not Finished> DrawSelf (DwS) 
            : Draws Itself
        | < Draw Rect
        | < Draw Circle
        | < Draw Polygon
        - >> DrawPolygon (Points[] , Amount , InternalColor) & DrawPolygonBorder (Points[] , Amount , BorderColor) >

    <Not Implemented> DrawText (Dwt)
            : Draws the text inside

    <Not Implemented> ClickDetection (ClkD)
            : Function activated on click

    <Not Implemented> DrawImage (DwImg)
            : Draws a image