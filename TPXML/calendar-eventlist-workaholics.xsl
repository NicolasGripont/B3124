<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <xsl:output method="html"/>
 
  <xsl:template match="/">
    <ul class="media-list">
      <xsl:for-each select="//event[contains(./title,'Workaholics')]">
        <li class="media"><xsl:apply-templates select="."/></li>
      </xsl:for-each>
    </ul>
  </xsl:template>


  <xsl:template match="event">
    <div class="media-body" id="./@uid">
      <h4><xsl:value-of select="./title"/></h4>
      <xsl:value-of select="substring(./dtstart,7,2)"/>-<xsl:value-of select="substring(./dtstart,5,2)"/>-<xsl:value-of select="substring(./dtstart,1,4)"/> / <xsl:value-of select="substring(./dtend,7,2)"/>-<xsl:value-of select="substring(./dtend,5,2)"/>-<xsl:value-of select="substring(./dtend,1,4)"/><br/>
      <xsl:value-of select="./summary"/><br/>
      <a href="{./url}"><xsl:value-of select="./url"/></a><br/>
      <xsl:value-of select="./description"/>
    </div>
    
  </xsl:template>

</xsl:stylesheet>

  