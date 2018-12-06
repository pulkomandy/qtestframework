<?xml version="1.0"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:template match="/Report">
		<html>
			<head>
				<title>Unit test report</title>
				<meta http-equiv='Content-Type' content='text/html' />
				<style>
					table { border-collapse: collapse; }
					table,tr,td,th { border: 1px solid black; }
				</style>
			</head>
			<body>
				<h1>UNIT TEST REPORT</h1>
				<xsl:for-each select="TestCase">
					<xsl:sort select="@name"/>
					<xsl:variable name="testname" select="@name" />
					<h2 id="{$testname}"><xsl:value-of select="@name" /></h2>
					<table CELLSPACING='0' CELLPADDING='2' >
						<thead><tr><TH>Function</TH><th>Tag</th><TH>Line</TH><TH>Result</TH><TH>Notification</TH><th>Duration</th></tr></thead>
						<tbody>
							<xsl:for-each select="TestFunction">
								<xsl:if test="@name != 'initTestCase' and @name != 'cleanupTestCase'">
									<xsl:for-each select="*[@type]">
									<xsl:variable name="pass" select="@type" />
									<xsl:choose>
										<xsl:when test="$pass = 'pass' or $pass = 'qdebug'">
											<tr>
												<td><xsl:value-of select="../@name" /></td>
												<td><xsl:value-of select="DataTag" /></td>
												<td> -- </td>
												<td><xsl:value-of select="$pass"/></td>
												<td><xsl:value-of select="Description" /></td>
												<td><xsl:value-of select="../Duration/@msecs" />ms</td>
											</tr>
										</xsl:when>

										<xsl:when test="$pass = 'qwarn'">
											<tr bgcolor="yellow"><td><xsl:value-of select="../@name" /></td>
												<td><xsl:value-of select="DataTag" /></td>
												<td><xsl:value-of select="@line" /></td>
												<td><xsl:value-of select="@type" /></td>
												<td><xsl:value-of select="Description" /></td>
												<td><xsl:value-of select="../Duration/@msecs" />ms</td>
											</tr>
										</xsl:when>
										<xsl:otherwise>
											<tr bgcolor="red"><td><xsl:value-of select="../@name" /></td>
												<td><xsl:value-of select="DataTag" /></td>
												<td><xsl:value-of select="@line" /></td>
												<td>FAILED</td>
												<td><xsl:value-of select="Description" /></td>
												<td><xsl:value-of select="../Duration/@msecs" />ms</td>
											</tr>
										</xsl:otherwise>
									</xsl:choose>
									</xsl:for-each>
								</xsl:if>
							</xsl:for-each>
						</tbody>
					</table>
				</xsl:for-each>   
	
			</body>
		</html>
	</xsl:template>
</xsl:stylesheet>
