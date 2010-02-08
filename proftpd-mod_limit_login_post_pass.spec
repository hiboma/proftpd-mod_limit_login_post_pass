%define module_name mod_limit_login_post_pass
%define hash 7ad12b9

Summary: A proftpd module enables Limit LOGIN directive in .ftpaccess ( post PASS  )
Name: proftpd-%{module_name}
Version: 0.1
Release: 1
License: Perl
Group: System Environment/Daemons
URL: http://github.com/hiboma/proftpd-%{module_name}
Source0: hiboma-proftpd-%{module_name}-%{hash}.tar.gz
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root
BuildRequires: proftpd proftpd-devel
Requires: proftpd

%description
A proftpd module enables Limit LOGIN directive in .ftpaccess ( post PASS  )

%prep
%setup -q -n hiboma-proftpd-%{module_name}-%{hash}

%build
%{_bindir}/prxs -c %{module_name}.c

%install
rm -rf   ${RPM_BUILD_ROOT}
mkdir -p ${RPM_BUILD_ROOT}%{_libexecdir}/proftpd
libtool --mode=install /usr/bin/install -c %{module_name}.la ${RPM_BUILD_ROOT}/%{_libexecdir}/proftpd

%clean
%{__rm} -rf %{buildroot}

%pre

%post

%preun

%postun

%files
%defattr(-,root,root,-)
%{_libexecdir}/proftpd/%{module_name}.a
%{_libexecdir}/proftpd/%{module_name}.la
%{_libexecdir}/proftpd/%{module_name}.so

%changelog
* Mon Feb 8 2010 Hiroya Ito <hiroyan@gmail.com> 0.1-1
 - wrote spec
