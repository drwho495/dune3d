# Version 1.0.90

## New Features

 - symmetry constraints ([5437a8c](https://github.com/horizon-eda/horizon/commit/5437a8c1be3d1696d55a7114a81088dc7e2ee9d1))
 - point in workplane constraint ([bc4c74f](https://github.com/horizon-eda/horizon/commit/bc4c74f667e2de1576600841038ba6e7aaa5d2ac))
 - selection filter ([7e13c45](https://github.com/horizon-eda/horizon/commit/7e13c45dc98a89471950ed3a6b3ad35a0e040420))
 - select all action ([a376f8e](https://github.com/horizon-eda/horizon/commit/a376f8e32e29c4064a47f79186e142cc88edae02))
 - deleted items popup ([9b8aea0](https://github.com/horizon-eda/horizon/commit/9b8aea0810dea6f47b9991fa5cd9b858e0d4d57c))
 - action for selecting underconstrained points ([3498e60](https://github.com/horizon-eda/horizon/commit/3498e602171d67c9c90cf78a674bfcf1d62036b7))
 - filtering for redundant constraints ([c48ea16](https://github.com/horizon-eda/horizon/commit/c48ea167efa27b90f272a75021fda129820ccbaa))

## Enhancements

 - link for finding redundant constraints ([bc6addb](https://github.com/horizon-eda/horizon/commit/bc6addb813635b9ed27bf32c52983a68a48c91b1))
 - properly handle zero-length lines in solid model generation ([a2752fe](https://github.com/horizon-eda/horizon/commit/a2752fe8ef4f50f6527d7a571d76373d28def64b))
 - zoom to cursor by default, add option for zooming to center ([6b14f51](https://github.com/horizon-eda/horizon/commit/6b14f51febf5a51bc6cd7345f4cdfe62828e7e94))
 - auto-generate unique group names ([a8777b8](https://github.com/horizon-eda/horizon/commit/a8777b828532cde263f1c2873caeceba7e7c423f))
 - automatically set active workplane when drawing the first workplane in a group ([3dacc3d](https://github.com/horizon-eda/horizon/commit/3dacc3d8e943ff16ff43ecd47e05bcb92fb93ecb))
 - turn canvas red if there are solver errors ([1a65cd0](https://github.com/horizon-eda/horizon/commit/1a65cd0c6be525c3b5c6d620fcbf85fad4b87f8a))
 - don't create redundant h/v constraints ([d024df5](https://github.com/horizon-eda/horizon/commit/d024df50555fe48ca5c537665f42b4229257e3e8))

## Bugfixes

 - STEP import: support uppercase extensions ([e3282cf](https://github.com/horizon-eda/horizon/commit/e3282cf6382064b281057b9d4df5683ae8d8402b))
 - properly handle undo when toggling body ([c5754a3](https://github.com/horizon-eda/horizon/commit/c5754a39d08bf343f52ec7e08cdae10938b13abe))
 - render constraint icons on zero-length lines ([618de51](https://github.com/horizon-eda/horizon/commit/618de513db19eca6c45eac4bef0b90ed21c36a6a))
 - keep digits after the comma when entering angles ([73033ce](https://github.com/horizon-eda/horizon/commit/73033ce86876c8d8dc6f418610015ba57d7e165a))
 - fix box selection on intel GPUs on windows ([cf38673](https://github.com/horizon-eda/horizon/commit/cf38673cbdab65898bc0ff5785afe0e17e70495a))
 - properly constrain points when drawing arcs ([74095ca](https://github.com/horizon-eda/horizon/commit/74095cae547bf88dc46e75661fc941c4fdbc2717))
 - fix extrude entities not converging after reloading document ([b97f544](https://github.com/horizon-eda/horizon/commit/b97f5440c56ce39186864b79052c69fd1ae9b87d))
 - prevent crash when opening context menu for constraining distance ([8b51b32](https://github.com/horizon-eda/horizon/commit/8b51b327c2432c1abf22e8b46e48334ae856a506))
 - prevent exception when deleting groups indirectly ([0e38d05](https://github.com/horizon-eda/horizon/commit/0e38d05f3143eb01b9918953485af749761b7cbb))
 - don't throw an exception when reordering groups in unsupported ways ([a62cebe](https://github.com/horizon-eda/horizon/commit/a62cebe59f15a6f0b61912416d104b80cd70f224))
 - cancel drag when pressing other mouse button ([9e0055f](https://github.com/horizon-eda/horizon/commit/9e0055fd8210bb3214d9e67b707a5664e908d468))
 - fix constraint icon and text selection ([d679ead](https://github.com/horizon-eda/horizon/commit/d679ead3ad5c8a5cd46e6999ee2382c498f919d1))
 - STEP import: fix things appearing at the origin ([38fb19c](https://github.com/horizon-eda/horizon/commit/38fb19c626c54921373f89c19b8a8e9540e5af95))
 - keep content locked to pointer when panning ([b8950de](https://github.com/horizon-eda/horizon/commit/b8950de7c1fb76cc476a4b199955ecc978e2edbd))
 - support nested solids for extrusion and lathe groups ([f777807](https://github.com/horizon-eda/horizon/commit/f777807b41c4dd87c25fe9cddf7e65adc06924dc))
 - don't crash when closing and re-opening log window ([f0257f2](https://github.com/horizon-eda/horizon/commit/f0257f2da931efc7eadada0445f37d0a128cee1a))
 - properly handle redundant constraints in some cases ([c0e7a4c](https://github.com/horizon-eda/horizon/commit/c0e7a4cd9e79ac2cc9b85088df839e05ef4d9182))

# Version 1.0.0

No change log since this is the first versioned release.
