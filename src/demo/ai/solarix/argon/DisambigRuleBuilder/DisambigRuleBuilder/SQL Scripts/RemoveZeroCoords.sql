DROP FUNCTION RemoveZeroCoords
GO

-- ================================================
-- Template generated from Template Explorer using:
-- Create Scalar Function (New Menu).SQL
--
-- Use the Specify Values for Template Parameters 
-- command (Ctrl-Shift-M) to fill in the parameter 
-- values below.
--
-- This block of comments will not be included in
-- the definition of the function.
-- ================================================
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date, ,>
-- Description:	<Description, ,>
-- =============================================
CREATE FUNCTION RemoveZeroCoords
(
	-- Add the parameters for the function here
 @str varchar(1000)
)
RETURNS varchar(1000)
AS
BEGIN

declare @res varchar(1000)

SET @res = REPLACE( @str, 'œ–»◊¿—“»≈:0', '' );
SET @res = REPLACE( @res, '~ –¿“ »…', '' );
SET @res = REPLACE( @res, 'ÃŒƒ¿À‹Õ€…:0', '' );
SET @res = REPLACE( @res, '  ', ' ' );
SET @res = REPLACE( @res, '  ', ' ' );

RETURN @res

END
GO

