<?xml version="1.0"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:template match="xml">
<html>
<body>
		<xsl:apply-templates/>
</body>
</html>
</xsl:template>
</xsl:stylesheet>