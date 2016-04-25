<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <xsl:output method="html"/>
  
  <xsl:template match="/">
    <html>
      <head>
        <title>
          <xsl:value-of select="//titre"/>
        </title>
      </head>
      <body style="background-color:white;">
        <xsl:apply-templates/>
      </body>
    </html>
  </xsl:template>

  <xsl:template match="entete">
    <table cellspacing="50" align="center">
      <tbody>
        <tr>
          <td>
            <img src="{infos/couverture/@chemin}"/>
          </td>
          <td>
            <h1 style="text-align:center; color:blue;">
              <xsl:value-of select="infos/titre"/>
            </h1>
            <h2 style="text-align:center; font-style: italic;">
              <xsl:value-of select="infos/auteur"/>
            </h2>
            <blockquote style="color:darkgreen;">But du TP du
              <xsl:value-of select="infos/date"/>:
              <xsl:value-of select="infos/but"/>
              <br/>

              <!-- AUTEURS -->
              <xsl:choose>
                <xsl:when test="count(infos/mise_en_forme_par/auteur) = 1">
                  Auteur :
                  <xsl:value-of select="infos/mise_en_forme_par/auteur[1]"/>
                </xsl:when>
                <xsl:when test="count(infos/mise_en_forme_par/auteur) &gt; 1">
                  Auteurs :
                  <xsl:for-each select="infos/mise_en_forme_par/auteur">
                    <xsl:value-of select="."/>                    
                    <xsl:choose>
                      <xsl:when test="position() != last() and position() != last()-1">, </xsl:when>
                    </xsl:choose>
                    <xsl:choose>
                      <xsl:when test="position() = last()-1"> et </xsl:when>
                    </xsl:choose>
                  </xsl:for-each>
                </xsl:when>
              </xsl:choose>
              
              <!-- NOBINOME -->
              <xsl:choose>
                <xsl:when test="count(//auteur/@NoBinome[not(preceding::auteur/@NoBinome=.)]) = 1">
                  (<xsl:value-of select="//infos/mise_en_forme_par/auteur/@NoBinome"/>)
                </xsl:when>
                <xsl:when test="count(//auteur/@NoBinome[not(preceding::auteur/@NoBinome=.)]) &gt; 1">
                  (<xsl:for-each select="//auteur/@NoBinome[not(preceding::auteur/@NoBinome=.)]">
                    <xsl:value-of select="."/>                    
                    <xsl:choose>
                      <xsl:when test="position() != last() and position() != last()-1">, </xsl:when>
                    </xsl:choose>
                    <xsl:choose>
                      <xsl:when test="position() = last()-1"> et </xsl:when>
                    </xsl:choose>
                  </xsl:for-each>)
                </xsl:when>
              </xsl:choose>
              
              <br/>
              Email du responsable:
              <xsl:value-of select="infos/email"/>
              <br/>
            </blockquote>
          </td>
        </tr>
      </tbody>
    </table>
  </xsl:template>

  <!-- CORPS -->
  <xsl:template match="corps">
    <hr/>
    <h3>Debut du texte:</h3>
    <xsl:apply-templates/>
    <h3>Fin du texte.</h3>
    <hr/>
  </xsl:template>

  <!-- NARRATION -->
  <xsl:template match="paragr[@type='narration']">
    <p>
      <xsl:for-each select="./phrase[@langue='fr']">
        <xsl:apply-templates select="."/>
      </xsl:for-each>
      <br/>
      <xsl:for-each select="./phrase[@langue='hu']">
        <xsl:apply-templates select="."/>
      </xsl:for-each>
    </p>
  </xsl:template>

  <!-- DIALOGUE -->
  <xsl:template match="paragr[@type='dialogue']">
    <table width="90%" align="center">
      <tbody>
        <tr>
          <td width="45%">
            <table width="100%" cellpadding="10" border="1">
              <tbody>
                <xsl:for-each select="./phrase[@langue='fr']">
                  <tr>
                    <td width="50" >
                      <img src="images/{@locuteur}.png"/>
                    </td>
                    <td>
                      <xsl:apply-templates select="."/>
                    </td>
                  </tr>
                </xsl:for-each>
              </tbody>
            </table>
          </td>
          <td/>
          <td width="45%">
            <table width="100%" cellpadding="10" border="1">
              <tbody>
                <xsl:for-each select="./phrase[@langue='hu']">
                  <tr>
                    <td width="50">
                      <img src="images/{@locuteur}.png"/>
                    </td>
                    <td>
                      <xsl:apply-templates select="."/>
                    </td>
                  </tr>
                </xsl:for-each>
              </tbody>
            </table>
          </td>
        </tr>
      </tbody>
    </table>
  </xsl:template>

  <!-- IMAGE -->
  <xsl:template match="image">
    <div align="center">
      <img>
        <xsl:attribute name="src">
          <xsl:value-of select="@chemin"/>
        </xsl:attribute>
      </img>
    </div>
  </xsl:template>
  

  <!-- Phrase FR -->
   <xsl:template match="phrase[@langue='fr']">
    <xsl:if  test="contains(.,'mouton')">
      <span style="font-size: 24px; font-weight: bold;">
        <xsl:value-of select="."/>
        <img src="images/moutonDessin.png" title="Mouton"/>
      </span>
    </xsl:if>
    <xsl:if  test="not(contains(.,'mouton'))">
        <span style="">
          <xsl:value-of select="."/>
        </span>
    </xsl:if>
  </xsl:template>

 <!-- Phrase HU -->
  <xsl:template match="phrase[@langue='hu']">
        <span style="font-style: italic; color: brown;">
          <xsl:value-of select="."/>
        </span>
  </xsl:template>

</xsl:stylesheet>







































