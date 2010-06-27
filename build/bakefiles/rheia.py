#
# Helper functions for Rheia bakefiles
#
# Author : Nicolas Macherey (nm@graymat.fr) http://www.rheia-framework.com
#


import utils

# We use 'CFG' option in places where bakefile doesn't like it, so we must
# register a substitution function for it that provides additional knowledge
# about the option (in this case that it does not contain dir separators and
# so utils.nativePaths() doesn't have to do anything with it):

try:
    # this fails in 0.1.4 and 0.1.5 has different subst.callbacks signature:
    utils.checkBakefileVersion('0.1.5') 
    def __noopSubst(name, func, caller):
        return '$(%s)' % name
except AttributeError:
    def __noopSubst(func, name):
        return '$(%s)' % name
utils.addSubstituteCallback('CFG', __noopSubst)
utils.addSubstituteCallback('LIBDIRNAME', __noopSubst)
utils.addSubstituteCallback('SETUPHDIR', __noopSubst)
utils.addSubstituteCallback('OBJS', __noopSubst)


def mk_rheiaid(id):
    """Creates Rheia library identifier from bakefile target ID that
       follows this convention: DLLs end with 'dll', static libraries
       end with 'lib'. If withPrefix=1, then _rheiaid is returned instead
       of rheiaid."""
    if id.endswith('dll') or id.endswith('lib'):
        rheia = id[:-3]
    else:
        rheia = id
    return rheia


# All libs that are part of the main library:
MAIN_LIBS = ['utils', 'base', 'loggers', 'packagemgt', 'workspacemgt', 'editor', 'python']

# List of library names/ids for categories with different names:
LIBS_GUI   = ['utils', 'base', 'loggers', 'packagemgt', 'workspacemgt', 'editor', 'python']

def mkLibName(rheiaid):
    """Returns string that can be used as library name, including name
       suffixes, prefixes, version tags etc. This must be kept in sync
       with variables defined in common.bkl!"""
    if rheiaid == 'mono':
        return '$(RHEIANAMEPREFIXGUI)$(RHEIANAMESUFFIX)$(RHEIAVERSIONTAG)$(HOST_SUFFIX)'
    if rheiaid in MAIN_LIBS:
        return '$(RHEIANAMEPREFIXGUI)$(RHEIANAMESUFFIX)_%s$(RHEIAVERSIONTAG)$(HOST_SUFFIX)' % rheiaid
    return '$(RHEIANAMEPREFIXGUI)$(RHEIANAMESUFFIX)_%s$(RHEIAVERSIONTAG)$(HOST_SUFFIX)' % rheiaid

def mkDllName(rheiaid):
    """Returns string that can be used as DLL name, including name
       suffixes, prefixes, version tags etc. This must be kept in sync
       with variables defined in common.bkl!"""
    if rheiaid == 'mono':
        return '$(RHEIADLLNAMEPREFIXGUI)$(RHEIANAMESUFFIX)$(RHEIACOMPILER)$(VENDORTAG)$(RHEIADLLVERSIONTAG)'
    if rheiaid in MAIN_LIBS:
        return '$(RHEIADLLNAMEPREFIXGUI)$(RHEIANAMESUFFIX)_%s$(RHEIACOMPILER)$(VENDORTAG)$(RHEIADLLVERSIONTAG)' % rheiaid
    return '$(RHEIADLLNAMEPREFIXGUI)$(RHEIANAMESUFFIX)_%s$(RHEIACOMPILER)$(VENDORTAG)$(RHEIADLLVERSIONTAG)' % rheiaid


def libToLink(rheialibname):
    """Returns string to pass to <sys-lib> when linking against 'wxlibname'.
       For one of main libraries, libToLink('foo') returns '$(RHEIALIB_FOO)' which
       must be defined in common.bkl as either nothing (in monolithic build) or
       mkLibName('foo') (otherwise).
       """
    if rheialibname in MAIN_LIBS:
        return '$(RHEIALIB_%s)' % rheialibname.upper()
    else:
        return mkLibName(rheialibname)

rheiaVersion = None
VERSION_FILE = '../../include/rheia/version.h'

def getVersion():
    """Returns Rheia version as a tuple: (major,minor,release)."""
    global rheiaVersion
    if rheiaVersion == None:
        f = open(VERSION_FILE, 'rt')
        lines = f.readlines()
        f.close()
        major = minor = release = None
        for l in lines:
            if not l.startswith('#define'): continue
            splitline = l.strip().split()
            if splitline[0] != '#define': continue
            if len(splitline) < 3: continue
            name = splitline[1]
            value = splitline[2]
            if value == None: continue
            if name == 'rheiaMAJOR_VERSION': major = int(value)
            if name == 'rheiaMINOR_VERSION': minor = int(value)
            if name == 'rheiaRELEASE_NUMBER': release = int(value)
            if major != None and minor != None and release != None:
                break
        rheiaVersion = (major, minor, release)
    return rheiaVersion

def getVersionMajor():
    return getVersion()[0]
def getVersionMinor():
    return getVersion()[1]
def getVersionRelease():
    return getVersion()[2]


def headersOnly(files):
    """Filters 'files' so that only headers are left. Used with
       <msvc-project-files> to add headers to VC++ projects but not files such
       as arrimpl.cpp."""
    
    def callback(cond, sources):
        prf = suf = ''
        if sources[0].isspace(): prf=' '
        if sources[-1].isspace(): suf=' '
        retval = []
        for s in sources.split():
            if s.endswith('.h'):
                retval.append(s)
        return '%s%s%s' % (prf, ' '.join(retval), suf)
    return utils.substitute2(files, callback)


def makeDspDependency(lib):
    """Returns suitable entry for <depends-on-dsp> for main libs."""
    return '%s:$(nativePaths(RHEIATOPDIR))build\\msw\\rheia_%s.dsp' % (lib,lib)
