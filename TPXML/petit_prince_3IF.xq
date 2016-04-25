(:1. Retournez les phrases en français triés en ordre alphabétique:)
(:
<phrases>
{ 
  for $p in doc("petit_prince_3IF.xml")//phrase[@langue="fr"]
  order by $p
  return $p 
}
</phrases>
:)

(:2. Retournez les phrases françaises contenant le mot "mouton":)
(:
<phrases>
{ 
  doc("petit_prince_3IF.xml")//phrase[@langue="fr" and contains(.,"mouton")]
}
</phrases>
:)

(:3. Pour chaque paragraphe: donnez son type, le nombre de phrases qui la compose, les modalités de ces phrases (sans répétition) ainsi que les locuteurs. (allez-y étape par étape). Astuce : pour avoir les valeurs uniques des modalités, utilisez la fonction distinct-values:)
(:
<paragraphes>
{ 
  for $paragr in doc("petit_prince_3IF.xml")//paragr
    let $phrases := $paragr/phrase
    return <paragraphe type="{$paragr/@type}" nbPhrases="{count($phrases)}">
    <modalitees>
    {
      for $modalite in distinct-values($paragr/phrase/@modalite)
        return <modalite> {$modalite} </modalite>
    }
    </modalitees>
    <locuteurs>
    {
      for $locuteur in distinct-values($paragr/phrase/@locuteur)
        return <locuteur> {$locuteur} </locuteur>
    }
    </locuteurs>
  </paragraphe>
}
</paragraphes>
:)

(: 4. Afficher la version française seulement (respectez la structure en paragraphes) :)
(: 
<paragraphes version="fr">
{ 
  for $paragr in doc("petit_prince_3IF.xml")//paragr
    return <paragraphe type="{$paragr/@type}">
    {
      for $phrase in $paragr/phrase[@langue="fr"]
        return $phrase
    }
  </paragraphe>
}
</paragraphes> 
:)

(: 5. Afficher uniquement les deuxièmes phrases des paragraphes de la version française :)
(: 
<phrases version="fr" rang="2">
{ 
  for $paragr in doc("petit_prince_3IF.xml")//paragr
    return  $paragr/phrase[@langue="fr" and position()=2]
}
</phrases> 
:) 

(: 6. Afficher seulement les dialogues en français du narrateur :)
(:
<paragraphes>
{ 
  for $paragr in doc("petit_prince_3IF.xml")//paragr[@type="dialogue"]
    return 
    if (count($paragr/phrase[@langue="fr" and @locuteur="Narrateur"]))
    then
      <paragraphe>
      {
        for $phrase in $paragr/phrase[@langue="fr" and @locuteur="Narrateur"]
          return $phrase
      }
      </paragraphe>
     else ()
}
</paragraphes>
:)

(: 7. Afficher toutes les phrases du Petit Prince en français qui comporte le mot "mouton" ainsi que le nombre de ces phrases :)

<phrases nbPhrases="{count(doc('petit_prince_3IF.xml')//paragr[@type='dialogue']/phrase[@locuteur='LePetitPrince' and @langue='fr' and contains(.,'mouton')])}">
{ 
  for $phrase in doc("petit_prince_3IF.xml")//paragr[@type="dialogue"]/phrase[@locuteur="LePetitPrince" and @langue="fr" and contains(.,"mouton")]
    return $phrase
}
</phrases>