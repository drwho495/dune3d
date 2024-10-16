# Version 1.1.91

As of [cb88440](https://github.com/dune3d/dune3d/commit/cb8844038aa8e0ca47b72a82589d31007ed75d13)

## New Features

 - add copy/paste ([b880274](https://github.com/dune3d/dune3d/commit/b8802743de03cb7dbeb14f64993d57f28312812f))
 - add body colors ([3f858f1](https://github.com/dune3d/dune3d/commit/3f858f158fc0a25f7f006e6f6f20eeeefe743bd6))
 - add text entities ([5dac357](https://github.com/dune3d/dune3d/commit/5dac35766a8cf86aa0fbb2a67a7c1dfc13d36b48))
 - add cluster entities ([c950380](https://github.com/dune3d/dune3d/commit/c9503801e41389b1f5b0355d40091b18e2bb2f65))
 - add DXF import ([270e757](https://github.com/dune3d/dune3d/commit/270e757acc73981a0f38b48f5967652ab754774d))
 - add bezier curves ([b4e5920](https://github.com/dune3d/dune3d/commit/b4e5920a49182dfe8c11d7d17d0b861648804d21), [aaf3e6f](https://github.com/dune3d/dune3d/commit/aaf3e6f6b5506fdc2600e8578f5d697b68e8e413))
 - add loft groups ([80450f5](https://github.com/dune3d/dune3d/commit/80450f5e0cbbb666f4fb9949e6ab37ee482366fc))
 - add revolve groups ([936aca6](https://github.com/dune3d/dune3d/commit/936aca66c6d214402d626edf27a4a04a641857f9))
 - workspace views for saving visible groups ([eeeca50](https://github.com/dune3d/dune3d/commit/eeeca50546caba676ddaaf2dd5c74acc29bad16c))
 - support linking documents as entities ([c78c9f7](https://github.com/dune3d/dune3d/commit/c78c9f79b06f41052ba7b702b8a3189a97b75840))
 - support multiple documents ([dd56445](https://github.com/dune3d/dune3d/commit/dd5644582a9b5d134db1575163d7afd7be618e34))
 - add keyboard pan/zoom/rotate ([55617b4](https://github.com/dune3d/dune3d/commit/55617b48873883dbf8e3837b27a37b3832b180df))
 - add menu for selecting obscured items ([760c851](https://github.com/dune3d/dune3d/commit/760c8510b762972c77ac0eda4ca84d5f0e400e2a))
 - add measurement constraints ([895f2b3](https://github.com/dune3d/dune3d/commit/895f2b36563c586a9f35274f7b44320fa12e30cb))

## Enhancements

 - improve rotation with new trackball scheme ([42d39ce](https://github.com/dune3d/dune3d/commit/42d39ce7fdd44f93ce71cce61e56bf1dc3967094))
 - add step model wireframe display mode ([8cc3b92](https://github.com/dune3d/dune3d/commit/8cc3b920f04315640928d271ffbf7b49263444ed))
 - show popup if a group couldn't be created ([c2cf03c](https://github.com/dune3d/dune3d/commit/c2cf03c1d735be527d853f0f65eff02a697348c4))
 - add opened documents to recent list on windows ([5032e94](https://github.com/dune3d/dune3d/commit/5032e94e20ab7e1c87bd635c166aed65e168b821))
 - show document path in header bar and workspace browser tooltip ([4fe0820](https://github.com/dune3d/dune3d/commit/4fe082083a42de88b0d0d4b31d9fe2824b52a857))
 - add tooltip for hover selection ([32155b5](https://github.com/dune3d/dune3d/commit/32155b514a17ff8143ed4ffc0da95adabcd01036))
 - make loading documents more tolerant to errors ([fcaa664](https://github.com/dune3d/dune3d/commit/fcaa664aebfa6f07665ac806acba87d960fc0297))
 - add option for showing construction entities from previous groups ([70df064](https://github.com/dune3d/dune3d/commit/70df064886264d04a62d02139c97d327f3edfc9f), [4aa0721](https://github.com/dune3d/dune3d/commit/4aa0721c66e4c15d878886a46ddd91d361078dd9))
 - show filename in window title ([160f897](https://github.com/dune3d/dune3d/commit/160f8971407540f18f0692e7fd8c0fa50b0f257f))
 - add STEP model reload button ([7203abf](https://github.com/dune3d/dune3d/commit/7203abff704111b8f20af34a51fc7ad22b569259))
 - use sensible default paths in file dialogs ([9fca904](https://github.com/dune3d/dune3d/commit/9fca904798ab9686c6228cf0c8efad3a275f5509))
 - draw contour tool: support tangent constraint on start point ([c8700c4](https://github.com/dune3d/dune3d/commit/c8700c4350c595c33216fcdd91df89f8b6bd2fab))
 - add option for hiding STEP solid model ([4fca12b](https://github.com/dune3d/dune3d/commit/4fca12b13e1f092d66cae6647c344b2eb5462f48))
 - let selected items glow, off by default ([8b2f77c](https://github.com/dune3d/dune3d/commit/8b2f77cec27476adba4cffd59362748e39875c1d))
 - automatically create tangent constraints when closing a contour ([e9bbf50](https://github.com/dune3d/dune3d/commit/e9bbf5075513ffc9b7502ac90a8bbb780255fd2d))
 - use different icons for sketch points depending on type ([f923ce0](https://github.com/dune3d/dune3d/commit/f923ce0d2cf7d095a8ac0bf726ff965cee641e07))
 - separate tool for point/line and point/plane distance constraints ([f0de1dd](https://github.com/dune3d/dune3d/commit/f0de1dd4e933794bc81370ac53d52fb02157585d))
 - put line/points perpendicular constraint in separate tool ([e6b9e64](https://github.com/dune3d/dune3d/commit/e6b9e64e7dcc0dcd7bef9160480260ff91df8fca))
 - put tangent constraints in separate tools ([8cc7da4](https://github.com/dune3d/dune3d/commit/8cc7da4c6c39a6e9147626f6c12d418031ed5c56))
 - replace Constrain coincident tool with tools for every constraint ([6272ebf](https://github.com/dune3d/dune3d/commit/6272ebf07530547366453f2d9d8f4a25fd274f96))
 - only show constrain equal radius/distance tool if just the right things are selected ([5fde27d](https://github.com/dune3d/dune3d/commit/5fde27dbeeef25fe74d01ebda88687784b3068bb))
 - only create constraints if at least one entity is in current group ([0e431c9](https://github.com/dune3d/dune3d/commit/0e431c9a0147fc489dd5e400da5f96892935d08b))


## Bugfixes

 - don't open the same document twice in two windows ([d5d2c6c](https://github.com/dune3d/dune3d/commit/d5d2c6c06db8d35d46829742c8b20b81ca90c1c0))
 - properly handle unknown item types ([37d65bd](https://github.com/dune3d/dune3d/commit/37d65bd4b585b03ab35c81e8686217aed62cb96d))
 - refresh array offset when updating group ([2f975bf](https://github.com/dune3d/dune3d/commit/2f975bfa4e914b2298adf21e30dae51a73b64963))
 - only accepts shortcuts when canvas has focus ([dffc6f0](https://github.com/dune3d/dune3d/commit/dffc6f0412b369fdaab1ba2e68ffb593b63c0a83))
 - properly reload changed STEP files without restarting the app ([07b4e8c](https://github.com/dune3d/dune3d/commit/07b4e8c3a567b87fdbffb26099b92010a92f7420))
 - allow solid model array in new body ([42963ec](https://github.com/dune3d/dune3d/commit/42963ec3ee77b4910caff434fe769b6b473c7ca0))
 - draw contour tool: properly add constraints when placing arc center ([cec8d37](https://github.com/dune3d/dune3d/commit/cec8d37f3d5110d670e0b7b3ad9504149ed3d677))
 - don't require pressing enter in group editor spin buttons ([bba8cbd](https://github.com/dune3d/dune3d/commit/bba8cbd0a6d30ffa5bbfc24f0d1b2e441b754fb4))
 - don't require pressing enter in selection editor ([f2c8c46](https://github.com/dune3d/dune3d/commit/f2c8c46879bf29fac197279bd9fbd7def6227c57))
 - properly save preferences when closing window ([55562da](https://github.com/dune3d/dune3d/commit/55562dac499784d5ba0fc6195a95646ea6d7a544))
 - increase max. distance length to 1km ([a7df8fd](https://github.com/dune3d/dune3d/commit/a7df8fd18fe98ac03fa143c4de1c0d24330257f8))

## Other changes
 - Arc/Arc tangent constraint is now called curve/curve tangent ([b821a47](https://github.com/dune3d/dune3d/commit/b821a47883e3df58e417c6e10852f93ca8f64646))

# Version 1.1.0

## New Features

 - symmetry constraints ([5437a8c](https://github.com/dune3d/dune3d/commit/5437a8c1be3d1696d55a7114a81088dc7e2ee9d1))
 - point in workplane constraint ([bc4c74f](https://github.com/dune3d/dune3d/commit/bc4c74f667e2de1576600841038ba6e7aaa5d2ac))
 - selection filter ([7e13c45](https://github.com/dune3d/dune3d/commit/7e13c45dc98a89471950ed3a6b3ad35a0e040420))
 - select all action ([a376f8e](https://github.com/dune3d/dune3d/commit/a376f8e32e29c4064a47f79186e142cc88edae02))
 - deleted items popup ([9b8aea0](https://github.com/dune3d/dune3d/commit/9b8aea0810dea6f47b9991fa5cd9b858e0d4d57c))
 - action for selecting underconstrained points ([3498e60](https://github.com/dune3d/dune3d/commit/3498e602171d67c9c90cf78a674bfcf1d62036b7))
 - filtering for redundant constraints ([c48ea16](https://github.com/dune3d/dune3d/commit/c48ea167efa27b90f272a75021fda129820ccbaa))

## Enhancements

 - link for finding redundant constraints ([bc6addb](https://github.com/dune3d/dune3d/commit/bc6addb813635b9ed27bf32c52983a68a48c91b1))
 - properly handle zero-length lines in solid model generation ([a2752fe](https://github.com/dune3d/dune3d/commit/a2752fe8ef4f50f6527d7a571d76373d28def64b))
 - zoom to cursor by default, add option for zooming to center ([6b14f51](https://github.com/dune3d/dune3d/commit/6b14f51febf5a51bc6cd7345f4cdfe62828e7e94))
 - auto-generate unique group names ([a8777b8](https://github.com/dune3d/dune3d/commit/a8777b828532cde263f1c2873caeceba7e7c423f))
 - automatically set active workplane when drawing the first workplane in a group ([3dacc3d](https://github.com/dune3d/dune3d/commit/3dacc3d8e943ff16ff43ecd47e05bcb92fb93ecb))
 - turn canvas red if there are solver errors ([1a65cd0](https://github.com/dune3d/dune3d/commit/1a65cd0c6be525c3b5c6d620fcbf85fad4b87f8a))
 - don't create redundant h/v constraints ([d024df5](https://github.com/dune3d/dune3d/commit/d024df50555fe48ca5c537665f42b4229257e3e8))
 - keep content locked to pointer when panning ([b8950de](https://github.com/dune3d/dune3d/commit/b8950de7c1fb76cc476a4b199955ecc978e2edbd))

## Bugfixes

 - STEP import: support uppercase extensions ([e3282cf](https://github.com/dune3d/dune3d/commit/e3282cf6382064b281057b9d4df5683ae8d8402b))
 - properly handle undo when toggling body ([c5754a3](https://github.com/dune3d/dune3d/commit/c5754a39d08bf343f52ec7e08cdae10938b13abe))
 - render constraint icons on zero-length lines ([618de51](https://github.com/dune3d/dune3d/commit/618de513db19eca6c45eac4bef0b90ed21c36a6a))
 - keep digits after the comma when entering angles ([73033ce](https://github.com/dune3d/dune3d/commit/73033ce86876c8d8dc6f418610015ba57d7e165a))
 - fix box selection on intel GPUs on windows ([cf38673](https://github.com/dune3d/dune3d/commit/cf38673cbdab65898bc0ff5785afe0e17e70495a))
 - properly constrain points when drawing arcs ([74095ca](https://github.com/dune3d/dune3d/commit/74095cae547bf88dc46e75661fc941c4fdbc2717))
 - fix extrude entities not converging after reloading document ([b97f544](https://github.com/dune3d/dune3d/commit/b97f5440c56ce39186864b79052c69fd1ae9b87d))
 - prevent crash when opening context menu for constraining distance ([8b51b32](https://github.com/dune3d/dune3d/commit/8b51b327c2432c1abf22e8b46e48334ae856a506))
 - prevent exception when deleting groups indirectly ([0e38d05](https://github.com/dune3d/dune3d/commit/0e38d05f3143eb01b9918953485af749761b7cbb))
 - don't throw an exception when reordering groups in unsupported ways ([a62cebe](https://github.com/dune3d/dune3d/commit/a62cebe59f15a6f0b61912416d104b80cd70f224))
 - cancel drag when pressing other mouse button ([9e0055f](https://github.com/dune3d/dune3d/commit/9e0055fd8210bb3214d9e67b707a5664e908d468))
 - fix constraint icon and text selection ([d679ead](https://github.com/dune3d/dune3d/commit/d679ead3ad5c8a5cd46e6999ee2382c498f919d1))
 - STEP import: fix things appearing at the origin ([38fb19c](https://github.com/dune3d/dune3d/commit/38fb19c626c54921373f89c19b8a8e9540e5af95))
 - support nested solids for extrusion and lathe groups ([f777807](https://github.com/dune3d/dune3d/commit/f777807b41c4dd87c25fe9cddf7e65adc06924dc))
 - don't crash when closing and re-opening log window ([f0257f2](https://github.com/dune3d/dune3d/commit/f0257f2da931efc7eadada0445f37d0a128cee1a))
 - properly handle redundant constraints in some cases ([c0e7a4c](https://github.com/dune3d/dune3d/commit/c0e7a4cd9e79ac2cc9b85088df839e05ef4d9182))

# Version 1.0.0

No change log since this is the first versioned release.
