<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="xml" encoding="ISO-8859-1" indent="yes"
      doctype-public="-//W3C//DTD XHTML 1.0 Transitional//EN"
      doctype-system="http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd"/>

  <xsl:variable name="href_base" select="''"/>
  <xsl:variable name="menu_name">Main Menu</xsl:variable>
<!--
 - returns the filename associated to an ID in the original file
 -->
  <xsl:template name="tocfilename">
    <xsl:param name="name" select="string(@href)"/>
    <xsl:choose>
      <xsl:when test="$name = '#Introducti'">
        <xsl:text>intro.html</xsl:text>
      </xsl:when>
      <xsl:when test="$name = '#Documentat'">
        <xsl:text>docs.html</xsl:text>
      </xsl:when>
      <xsl:when test="$name = '#Reporting'">
        <xsl:text>bugs.html</xsl:text>
      </xsl:when>
      <xsl:when test="$name = '#help'">
        <xsl:text>help.html</xsl:text>
      </xsl:when>
      <xsl:when test="$name = '#Help'">
        <xsl:text>help.html</xsl:text>
      </xsl:when>
      <xsl:when test="$name = '#Downloads'">
        <xsl:text>downloads.html</xsl:text>
      </xsl:when>
      <xsl:when test="$name = '#News'">
        <xsl:text>news.html</xsl:text>
      </xsl:when>
      <xsl:when test="$name = '#Contributi'">
        <xsl:text>contribs.html</xsl:text>
      </xsl:when>
      <xsl:when test="$name = '#xsltproc'">
        <xsl:text>xsltproc2.html</xsl:text>
      </xsl:when>
      <xsl:when test="$name = '#API'">
        <xsl:text></xsl:text>
      </xsl:when>
      <xsl:when test="$name = '#XSLT'">
        <xsl:text>XSLT.html</xsl:text>
      </xsl:when>
      <xsl:when test="$name = '#XML'">
        <xsl:text>XMLinfo.html</xsl:text>
      </xsl:when>
      <xsl:when test="$name = '#Validation'">
        <xsl:text>xmldtd.html</xsl:text>
      </xsl:when>
      <xsl:when test="$name = '#tree'">
        <xsl:text></xsl:text>
      </xsl:when>
      <xsl:when test="$name = '#library'">
        <xsl:text></xsl:text>
      </xsl:when>
      <xsl:when test="$name = '#interface'">
        <xsl:text></xsl:text>
      </xsl:when>
      <xsl:when test="$name = '#Example'">
        <xsl:text></xsl:text>
      </xsl:when>
      <xsl:when test="$name = '#Entities'">
        <xsl:text></xsl:text>
      </xsl:when>
      <xsl:when test="$name = '#architecture'">
        <xsl:text>architecture.html</xsl:text>
      </xsl:when>
      <xsl:when test="$name = '#Namespaces'">
        <xsl:text>namespaces.html</xsl:text>
      </xsl:when>
      <xsl:when test="$name = '#DOM'">
        <xsl:text></xsl:text>
      </xsl:when>
      <xsl:when test="$name = '#Catalog'">
        <xsl:text>catalog.html</xsl:text>
      </xsl:when>
      <xsl:when test="$name = '#Upgrading'">
        <xsl:text></xsl:text>
      </xsl:when>
      <xsl:when test="$name = '#Encodings'">
        <xsl:text>encoding.html</xsl:text>
      </xsl:when>
      <xsl:when test="$name = '#IO'">
        <xsl:text></xsl:text>
      </xsl:when>
      <xsl:when test="$name = '#Memory'">
        <xsl:text></xsl:text>
      </xsl:when>
      <xsl:when test="$name = '#Thread'">
        <xsl:text></xsl:text>
      </xsl:when>
      <xsl:when test="$name = '#FAQ'">
        <xsl:text>FAQ.html</xsl:text>
      </xsl:when>
      <xsl:when test="$name = '#Python'">
        <xsl:text></xsl:text>
      </xsl:when>
      <xsl:when test="$name = ''">
        <xsl:text>unknown.html</xsl:text>
      </xsl:when>
      <xsl:otherwise>
        <xsl:value-of select="$name"/>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>
  <xsl:template name="filename">
    <xsl:param name="name" select="string(@href)"/>
    <xsl:choose>
      <xsl:when test="$name = '#Introducti'">
        <xsl:text>intro.html</xsl:text>
      </xsl:when>
      <xsl:when test="$name = '#Documentat'">
        <xsl:text>docs.html</xsl:text>
      </xsl:when>
      <xsl:when test="$name = '#Reporting'">
        <xsl:text>bugs.html</xsl:text>
      </xsl:when>
      <xsl:when test="$name = '#help'">
        <xsl:text>help.html</xsl:text>
      </xsl:when>
      <xsl:when test="$name = '#Help'">
        <xsl:text>help.html</xsl:text>
      </xsl:when>
      <xsl:when test="$name = '#Downloads'">
        <xsl:text>downloads.html</xsl:text>
      </xsl:when>
      <xsl:when test="$name = '#News'">
        <xsl:text>news.html</xsl:text>
      </xsl:when>
      <xsl:when test="$name = '#Contributi'">
        <xsl:text>contribs.html</xsl:text>
      </xsl:when>
      <xsl:when test="$name = '#xsltproc'">
        <xsl:text>xsltproc2.html</xsl:text>
      </xsl:when>
      <xsl:when test="$name = '#API'">
        <xsl:text></xsl:text>
      </xsl:when>
      <xsl:when test="$name = '#XSLT'">
        <xsl:text>XSLT.html</xsl:text>
      </xsl:when>
      <xsl:when test="$name = '#XML'">
        <xsl:text>XMLinfo.html</xsl:text>
      </xsl:when>
      <xsl:when test="$name = '#Validation'">
        <xsl:text>xmldtd.html</xsl:text>
      </xsl:when>
      <xsl:when test="$name = '#tree'">
        <xsl:text></xsl:text>
      </xsl:when>
      <xsl:when test="$name = '#library'">
        <xsl:text></xsl:text>
      </xsl:when>
      <xsl:when test="$name = '#interface'">
        <xsl:text></xsl:text>
      </xsl:when>
      <xsl:when test="$name = '#Example'">
        <xsl:text></xsl:text>
      </xsl:when>
      <xsl:when test="$name = '#Entities'">
        <xsl:text></xsl:text>
      </xsl:when>
      <xsl:when test="$name = '#architecture'">
        <xsl:text>architecture.html</xsl:text>
      </xsl:when>
      <xsl:when test="$name = '#Namespaces'">
        <xsl:text>namespaces.html</xsl:text>
      </xsl:when>
      <xsl:when test="$name = '#DOM'">
        <xsl:text></xsl:text>
      </xsl:when>
      <xsl:when test="$name = '#Catalog'">
        <xsl:text>catalog.html</xsl:text>
      </xsl:when>
      <xsl:when test="$name = '#Upgrading'">
        <xsl:text></xsl:text>
      </xsl:when>
      <xsl:when test="$name = '#Encodings'">
        <xsl:text>encoding.html</xsl:text>
      </xsl:when>
      <xsl:when test="$name = '#IO'">
        <xsl:text></xsl:text>
      </xsl:when>
      <xsl:when test="$name = '#Memory'">
        <xsl:text></xsl:text>
      </xsl:when>
      <xsl:when test="$name = '#Thread'">
        <xsl:text></xsl:text>
      </xsl:when>
      <xsl:when test="$name = '#FAQ'">
        <xsl:text>FAQ.html</xsl:text>
      </xsl:when>
      <xsl:when test="$name = '#Python'">
        <xsl:text></xsl:text>
      </xsl:when>
      <xsl:when test="$name = ''">
        <xsl:text>unknown.html</xsl:text>
      </xsl:when>
      <xsl:otherwise>
        <xsl:value-of select="$name"/>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>
<!--
 - The global title
 -->
  <xsl:variable name="globaltitle" select="string(/html/body/h1[1])"/>

<!--
  the main menu box
 -->
  <xsl:template name="mainmenu">
   <div class="left">
    <form action="search.php"
          enctype="application/x-www-form-urlencoded" method="get">
      <input name="query" type="text" size="20" value=""/>
      <input name="submit" type="submit" value="Search ..."/>
    </form>
    <div class="box">
      <h2 class="box_title">main menu</h2>
    </div>
    <p><a href="{$href_base}index.html">Home</a></p>
    <xsl:for-each select="/html/body/h2">
    <xsl:variable name="filename">
      <xsl:call-template name="tocfilename">
	<xsl:with-param name="name" select="concat('#', string(a[1]/@name))"/>
      </xsl:call-template>
    </xsl:variable>
    <xsl:if test="$filename != ''">
      <p>
	<xsl:element name="a">
	  <xsl:attribute name="href">
	    <xsl:value-of select="$filename"/>
	  </xsl:attribute>
	  <xsl:if test="$filename = 'docs.html'">
	      <xsl:attribute name="style">font-weight:bold</xsl:attribute>
	  </xsl:if>
	  <xsl:value-of select="."/>
	</xsl:element>
      </p>
    </xsl:if>
    </xsl:for-each>
    <p><a style="font-weight:bold"
             href="html/index.html">API Menu</a></p>
      <p><a href="ChangeLog.html">Recent Changes</a></p>

    <div class="box">
      <h2 class="box_title">related links</h2>
    </div>
    <p><a href="https://www.redhat.com/archives/libvir-list/">Mail archive</a></p>
    <p><a href="http://www.cl.cam.ac.uk/Research/SRG/netos/xen/index.html">Xen project</a></p>
    <a href="http://xmlsoft.org/"><img src="{$href_base}Libxml2-Logo-90x34.gif" alt="Made with Libxml2 Logo"/></a>
   </div>
  </xsl:template>

<!--
  the main menu box
 -->
  <xsl:template name="develtoc">
   <div class="left">
    <form action="search.php"
          enctype="application/x-www-form-urlencoded" method="get">
      <input name="query" type="text" size="20" value=""/>
      <input name="submit" type="submit" value="Search ..."/>
    </form>
    <div class="box">
      <h2 class="box_title">API menu</h2>
    </div>
      <p><a href="{$href_base}index.html">Main menu</a></p>
      <p><a href="{$href_base}/html/index.html">API menu</a></p>
      <p><a href="{$href_base}ChangeLog.html">ChangeLog</a></p>
    <div class="box">
      <h2 class="box_title">API Indexes</h2>
    </div>
      <p><a href="{$href_base}APIchunk0.html">Alphabetic</a></p>
      <p><a href="{$href_base}APIconstructors.html">Constructors</a></p>
      <p><a href="{$href_base}APIfunctions.html">Functions/Types</a></p>
      <p><a href="{$href_base}APIfiles.html">Modules</a></p>
      <p><a href="{$href_base}APIsymbols.html">Symbols</a></p>
    <div class="box">
      <h2 class="box_title">related links</h2>
    </div>
    <p><a href="https://www.redhat.com/archives/libvir-list/">Mail archive</a></p>
    <p><a href="http://www.cl.cam.ac.uk/Research/SRG/netos/xen/index.html">Xen project</a></p>
    <a href="http://xmlsoft.org/"><img src="{$href_base}Libxml2-Logo-90x34.gif" alt="Made with Libxml2 Logo"/></a>
   </div>
  </xsl:template>

<!--
  the menu box for developper's pages
 -->
<!--
  the page title
 -->

  <xsl:template name="titlebox">
    <xsl:param name="title"/>
    <h3 class="title"><xsl:value-of select="$title"/></h3>
  </xsl:template>

<!--
 - Write the styles in the head
 -->
  <xsl:template name="style">
    <link rel="stylesheet" type="text/css" href="{$href_base}libvir.css" />
  </xsl:template>

<!--
 - The top section 
 -->
  <xsl:template name="top">
    <div id="top">
      <img src="{$href_base}libvirHeader.png" alt="Libvir the virtualization API" />
    </div>
  </xsl:template>

<!--
 - The top section for the main page
 -->
  <xsl:template name="topmain">
    <div id="topmain">
      <img src="{$href_base}libvirLogo.png" alt="Libvir the virtualization API" />
    </div>
  </xsl:template>

<!--
 - The bottom section
 -->
  <xsl:template name="bottom">
    <div id="copyright"> </div> 
  </xsl:template>

<!--
 - Handling of nodes in the body after an H2
 - Open a new file and dump all the siblings up to the next H2
 -->
  <xsl:template name="subfile">
    <xsl:param name="header" select="following-sibling::h2[1]"/>
    <xsl:variable name="filename">
      <xsl:call-template name="filename">
        <xsl:with-param name="name" select="concat('#', string($header/a[1]/@name))"/>
      </xsl:call-template>
    </xsl:variable>
    <xsl:variable name="title">
      <xsl:value-of select="$header"/>
    </xsl:variable>
    <xsl:document href="{$filename}" method="xml" encoding="ISO-8859-1"
      doctype-public="-//W3C//DTD XHTML 1.0 Transitional//EN"
      doctype-system="http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
      <html>
        <head>
          <xsl:call-template name="style"/>
          <xsl:element name="title">
            <xsl:value-of select="$title"/>
          </xsl:element>
        </head>
        <body>
	  <div id="main">
	    <xsl:call-template name="top"/>
	    <div id="left">
	      <xsl:call-template name="mainmenu"/>
	    </div>
	    <div id="right">
	      <xsl:call-template name="titlebox">
		<xsl:with-param name="title" select="$title"/>
	      </xsl:call-template>
	      <xsl:apply-templates mode="subfile" select="$header/following-sibling::*[preceding-sibling::h2[1] = $header and name() != 'h2' ]"/>
	    </div>
	    <xsl:call-template name="bottom"/>
	  </div>
        </body>
      </html>
    </xsl:document>
  </xsl:template>

  <xsl:template mode="subcontent" match="@*|node()">
    <xsl:copy>
      <xsl:apply-templates mode="subcontent" select="@*|node()"/>
    </xsl:copy>
  </xsl:template>

  <xsl:template mode="content" match="@*|node()">
    <xsl:if test="name() != 'h1' and name() != 'h2'">
      <xsl:copy>
        <xsl:apply-templates mode="subcontent" select="@*|node()"/>
      </xsl:copy>
    </xsl:if>
  </xsl:template>

  <xsl:template mode="subfile" match="@*|node()">
    <xsl:copy>
      <xsl:apply-templates mode="content" select="@*|node()"/>
    </xsl:copy>
  </xsl:template>

<!--
 - Handling of the initial body and head HTML document
 -->
  <xsl:template match="body">
    <xsl:variable name="firsth2" select="./h2[1]"/>
    <body>
      <div id="main">
	<xsl:call-template name="topmain"/>
        <div id="left">
	  <xsl:call-template name="mainmenu"/>
        </div>
        <div id="right">
          <xsl:apply-templates mode="content" select="($firsth2/preceding-sibling::*)"/>
          <xsl:for-each select="./h2">
            <xsl:call-template name="subfile">
	      <xsl:with-param name="header" select="."/>
            </xsl:call-template>
          </xsl:for-each>
        </div>
        <xsl:call-template name="bottom"/>
      </div>
    </body>
  </xsl:template>
  <xsl:template match="head">
  </xsl:template>
  <xsl:template match="html">
    <xsl:message>Generating the Web pages</xsl:message>
    <html>
      <head>
        <xsl:call-template name="style"/>
        <title>the virtualization API</title>
      </head>
      <xsl:apply-templates/>
    </html>
  </xsl:template>
</xsl:stylesheet>
